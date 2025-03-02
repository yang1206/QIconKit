//
// Created by Yang1206 on 2025/3/2.
//

#include "QIconKit/icon_factories.h"
#include <QMap>
#include <QtCore/qcoreapplication.h>

namespace QIconKit {

// RemixIcon工厂实现
RemixIconFactory& RemixIconFactory::instance() {
    static RemixIconFactory instance;
    return instance;
}

RemixIconFactory::RemixIconFactory()
    : FontIconProvider("RemixIcon", ":/fonts/fonts/RemixIcon.ttf") {
}

QIcon RemixIconFactory::icon(Remix::Icon icon, int size, const QColor& color) const {
    return iconFromCode(static_cast<int>(icon), size, color);
}

// LucideIcon工厂实现
LucideIconFactory& LucideIconFactory::instance() {
    static LucideIconFactory instance;
    return instance;
}

LucideIconFactory::LucideIconFactory()
    : FontIconProvider("Lucide", ":/fonts/fonts/Lucide.ttf") {
}

QIcon LucideIconFactory::icon(Lucide::Icon icon, int size, const QColor& color) const {
    return iconFromCode(static_cast<int>(icon), size, color);
}

// FontAwesome工厂实现
FontAwesomeIconFactory& FontAwesomeIconFactory::instance() {
    static FontAwesomeIconFactory instance;
    return instance;
}

FontAwesomeIconFactory::FontAwesomeIconFactory()
    : FontIconProvider("FontAwesome", ":/fonts/fonts/FontAwesome.ttf") {
}

QIcon FontAwesomeIconFactory::icon(FontAwesome::Icon icon, int size, const QColor& color) const {
    return iconFromCode(static_cast<int>(icon), size, color);
}

// MaterialIcon工厂实现
// 在现有的icon_factories.cpp文件中添加以下内容

// 初始化静态成员
QMap<Material::Style, MaterialIconFactory*> MaterialIconFactory::s_instances;

MaterialIconFactory& MaterialIconFactory::instance(Material::Style style) {
    if (!s_instances.contains(style)) {
        s_instances[style] = new MaterialIconFactory(style);
    }
    return *s_instances[style];
}

MaterialIconFactory::MaterialIconFactory(Material::Style style):FontIconProvider("", ""),
     m_style(style) {
    // 根据样式选择不同的字体文件
    QString fontFile;
    QString fontFamily;

    switch (style) {
        case Material::Style::Filled:
            fontFile = ":/fonts/fonts/MaterialIcons-Regular.ttf";
            fontFamily = "Material Icons";
            break;
        case Material::Style::Outlined:
            fontFile = ":/fonts/fonts/MaterialIconsOutlined-Regular.otf";
            fontFamily = "Material Icons Outlined";
            break;
        case Material::Style::Rounded:
            fontFile = ":/fonts/fonts/MaterialIconsRound-Regular.otf";
            fontFamily = "Material Icons Round";
            break;
        case Material::Style::Sharp:
            fontFile = ":/fonts/fonts/MaterialIconsSharp-Regular.otf";
            fontFamily = "Material Icons Sharp";
            break;
    }

    // 初始化基类
    m_fontResource = fontFile;
    m_fontFamily = fontFamily;
}

QIcon MaterialIconFactory::filledIcon(Material::Filled::Icon icon, int size, const QColor& color) const {
    return iconFromCode(static_cast<int>(icon), size, color);
}

QIcon MaterialIconFactory::outlinedIcon(Material::Outlined::Icon icon, int size, const QColor& color) const {
    return iconFromCode(static_cast<int>(icon), size, color);
}

QIcon MaterialIconFactory::roundedIcon(Material::Rounded::Icon icon, int size, const QColor& color) const {
    return iconFromCode(static_cast<int>(icon), size, color);
}

QIcon MaterialIconFactory::sharpIcon(Material::Sharp::Icon icon, int size, const QColor& color) const {
    return iconFromCode(static_cast<int>(icon), size, color);
}


QIcon MaterialIconFactory::icon(int iconCode, Material::Style style, int size, const QColor& color) const {
    // 如果请求的样式与当前实例的样式不匹配，则获取正确的实例
    if (style != m_style) {
        return instance(style).icon(iconCode, style, size, color);
    }

    return iconFromCode(iconCode, size, color);
}


} // namespace QtIcons