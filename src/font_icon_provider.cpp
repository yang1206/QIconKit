//
// Created by Yang1206 on 2025/3/2.
//

#include "QIconKit/font_icon_provider.h"
#include <QFile>
#include <QGuiApplication>
#include <QPainter>
#include <QPixmap>
#include <QScreen>

#include "QIconKit/icon_cache.h"

namespace QIconKit {

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
    // qDebug() << "成功加载字体:" << m_fontResource << "字体族:" << m_fontFamily;
    return true;
}

QIcon FontIconProvider::iconFromCode(int iconCode, int size, const QColor& color) const {
    // 尝试从缓存获取图标
    QIcon cachedIcon = IconCache::instance().getIcon(m_fontFamily, iconCode, size, color);
    if (!cachedIcon.isNull()) {
        return cachedIcon;
    }

    // 如果缓存中不存在，则渲染图标
    QIcon icon = renderIcon(iconCode, size, color);

    // 将渲染的图标添加到缓存
    IconCache::instance().getIcon(m_fontFamily, iconCode, size, color) = icon;

    return icon;
}


QString FontIconProvider::fontFamily() const {
    return m_fontFamily;
}

QIcon FontIconProvider::renderIcon(int iconCode, int size, const QColor& color) const {
    if (m_fontId < 0) {
        return QIcon();
    }

    QIcon icon;

    // 获取设备像素比
    qreal dpr = qApp->devicePixelRatio();

    // 为4K屏幕优化，创建更多尺寸的图标
    QList<int> sizes;
    // 基础尺寸
    sizes << size;
    // 2倍尺寸 (适合普通高DPI)
    sizes << size * 2;
    // 4倍尺寸 (适合4K屏幕)
    sizes << size * 4;

    for (int pixelSize : sizes) {
        // 创建足够大的图像以适应高分辨率
        int actualSize = pixelSize;
        QPixmap pixmap(actualSize, actualSize);
        pixmap.fill(Qt::transparent);

        QPainter painter;
        painter.begin(&pixmap);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
        painter.setPen(color);

        QFont font(m_fontFamily);
        // 确保字体大小与图标大小匹配
        font.setPixelSize(actualSize * 0.9); // 稍微调整以确保图标完全显示
        painter.setFont(font);

        // 在图标中心绘制文本
        QString text = QString(QChar(iconCode));
        painter.drawText(QRect(0, 0, actualSize, actualSize), Qt::AlignCenter, text);
        painter.end();

        // 设置设备像素比
        pixmap.setDevicePixelRatio(1.0); // 确保不会被自动缩放

        // 为不同尺寸添加到图标
        icon.addPixmap(pixmap, QIcon::Normal, QIcon::Off);
        icon.addPixmap(pixmap, QIcon::Normal, QIcon::On);
        icon.addPixmap(pixmap, QIcon::Disabled, QIcon::Off);
        icon.addPixmap(pixmap, QIcon::Disabled, QIcon::On);
        icon.addPixmap(pixmap, QIcon::Active, QIcon::Off);
        icon.addPixmap(pixmap, QIcon::Active, QIcon::On);
        icon.addPixmap(pixmap, QIcon::Selected, QIcon::Off);
        icon.addPixmap(pixmap, QIcon::Selected, QIcon::On);
    }

    return icon;
}

} // namespace QtIcons