//
// Created by Yang1206 on 2025/3/2.
//

#ifndef ICON_FACTORIES_H
#define ICON_FACTORIES_H

#include "font_icon_provider.h"
#include "enums/remix_icons.h"
#include "enums/lucide_icons.h"
#include "enums/font_awesome.h"
#include "enums/material_icons.h"

namespace QtIcons {

// Remix图标工厂
class QTICONS_EXPORT RemixIconFactory : public FontIconProvider {
public:
    static RemixIconFactory& instance();

    // 从枚举获取图标
    QIcon icon(Remix::Icon icon, int size = 16, const QColor& color = QColor(0, 0, 0)) const;

private:
    RemixIconFactory();
};

class QTICONS_EXPORT LucideIconFactory : public FontIconProvider {
public:
    static LucideIconFactory& instance();

    // 从枚举获取图标
    QIcon icon(Lucide::Icon icon, int size = 16, const QColor& color = QColor(0, 0, 0)) const;

private:
    LucideIconFactory();
};

// FontAwesome图标工厂
class FontAwesomeIconFactory : public FontIconProvider {
public:
    static FontAwesomeIconFactory& instance();

    // 从枚举获取图标
    QIcon icon(FontAwesome::Icon icon, int size = 16, const QColor& color = QColor(0, 0, 0)) const;

private:
    FontAwesomeIconFactory();
};

class QTICONS_EXPORT MaterialIconFactory : public FontIconProvider {
public:
    static MaterialIconFactory& instance(Material::Style style = Material::Style::Filled);

    // 获取图标 - 各种变体
    QIcon filledIcon(Material::Filled::Icon icon, int size, const QColor& color) const;
    QIcon outlinedIcon(Material::Outlined::Icon icon, int size, const QColor& color) const;
    QIcon roundedIcon(Material::Rounded::Icon icon, int size, const QColor& color) const;
    QIcon sharpIcon(Material::Sharp::Icon icon, int size, const QColor& color) const;
    QIcon twoToneIcon(Material::TwoTone::Icon icon, int size, const QColor& color, const QColor& secondaryColor = QColor(0, 0, 0, 38)) const;

    // 通用方法 - 根据变体类型获取图标
    QIcon icon(int iconCode, Material::Style style, int size, const QColor& color, const QColor& secondaryColor = QColor(0, 0, 0, 38)) const;

private:
    explicit MaterialIconFactory(Material::Style style);

    // 存储不同变体的字体提供者
    static QMap<Material::Style, MaterialIconFactory*> s_instances;
    Material::Style m_style;

};

// 这里可以添加更多图标工厂类...

} // namespace QtIcons

#endif //ICON_FACTORIES_H