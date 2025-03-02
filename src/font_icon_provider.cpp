//
// Created by Yang1206 on 2025/3/2.
//

#include "QtIcons/font_icon_provider.h"
#include <QPainter>
#include <QPixmap>
#include <QFile>
#include <QGuiApplication>
#include <QScreen>

namespace QtIcons {

FontIconProvider::FontIconProvider(const QString& fontFamily, const QString& fontResource)
    : m_fontFamily(fontFamily), m_fontResource(fontResource) {
}

bool FontIconProvider::loadFont() {
    if (m_fontId >= 0) {
        return true; // 已加载
    }

    QFile fontFile(m_fontResource);
    if (!fontFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    QByteArray fontData = fontFile.readAll();
    fontFile.close();

    m_fontId = QFontDatabase::addApplicationFontFromData(fontData);

    if (m_fontId < 0) {
        qWarning() << "加载字体失败:" << m_fontResource;
        return false;
    }

    // 获取字体加载后的实际字体族名称
    QStringList families = QFontDatabase::applicationFontFamilies(m_fontId);
    if (families.isEmpty()) {
        qWarning() << "字体加载成功但没有找到字体族:" << m_fontResource;
        return false;
    }

    // 使用实际的字体族名称，而不是构造函数中提供的名称
    m_fontFamily = families.first();
    qDebug() << "成功加载字体:" << m_fontResource << "字体族:" << m_fontFamily;
    return true;
}

QIcon FontIconProvider::iconFromCode(int iconCode, int size, const QColor& color) const {
    return renderIcon(iconCode, size, color);
}

QIcon FontIconProvider::twoToneIconFromCode(int iconCode, int size, const QColor& primaryColor, const QColor& secondaryColor) const {
    return renderTwoToneIcon(iconCode, size, primaryColor, secondaryColor);
}

QString FontIconProvider::fontFamily() const {
    return m_fontFamily;
}

QIcon FontIconProvider::renderIcon(int iconCode, int size, const QColor& color) const {
    if (m_fontId < 0) {
        return QIcon();
    }

    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    QFont font = QFont(m_fontFamily);
    font.setPixelSize(size);
    painter.setFont(font);
    painter.setPen(color);

    QString text = QString(QChar(iconCode));
    painter.drawText(pixmap.rect(), Qt::AlignCenter, text);

    return QIcon(pixmap);
}

QIcon FontIconProvider::renderTwoToneIcon(int iconCode, int size, const QColor& primaryColor, const QColor& secondaryColor) const {
    if (m_fontId < 0) {
        return QIcon();
    }

    QPixmap pixmap(size, size);
    pixmap.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    QFont font = QFont(m_fontFamily);
    font.setPixelSize(size);
    painter.setFont(font);


    QString text = QString(QChar(iconCode));

    // 先绘制次要颜色部分
    painter.setPen(secondaryColor);
    painter.drawText(pixmap.rect(), text);

    // 再绘制主要颜色部分
    painter.setPen(primaryColor);
    painter.drawText(pixmap.rect(), text);

    return QIcon(pixmap);
}


} // namespace QtIcons