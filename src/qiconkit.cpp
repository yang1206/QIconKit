//
// Created by Yang1206 on 2025/3/2.
//

#include "QIconKit/qiconkit.h"
#include "QIconKit/icon_manager.h"
#include <memory>

namespace QIconKit {

bool QIconKit::initialize() {
    bool success = true;

    // 注册并加载RemixIcon
    IconManager::instance().registerProvider("RemixIcon",
        std::shared_ptr<IconProvider>(&RemixIconFactory::instance(),
        [](IconProvider*){})); // 使用空删除器，因为单例不应被删除

    success &= RemixIconFactory::instance().loadFont();

    // 注册并加载LucideIcon
    IconManager::instance().registerProvider("LucideIcon",
        std::shared_ptr<IconProvider>(&LucideIconFactory::instance(),
        [](IconProvider*){})); // 使用空删除器，因为单例不应被删除

    success &= LucideIconFactory::instance().loadFont();

    // 注册并加载FontAwesome
    IconManager::instance().registerProvider("FontAwesome",
        std::shared_ptr<IconProvider>(&FontAwesomeIconFactory::instance(),
        [](IconProvider*){})); // 使用空删除器，因为单例不应被删除

    success &= FontAwesomeIconFactory::instance().loadFont();

    // 初始化Material Icons各变体
    IconManager::instance().registerProvider("MaterialFilled",
        std::shared_ptr<IconProvider>(&MaterialIconFactory::instance(Material::Style::Filled),
        [](IconProvider*){}));
    success &= MaterialIconFactory::instance(Material::Style::Filled).loadFont();

    IconManager::instance().registerProvider("MaterialOutlined",
        std::shared_ptr<IconProvider>(&MaterialIconFactory::instance(Material::Style::Outlined),
        [](IconProvider*){}));
    success &= MaterialIconFactory::instance(Material::Style::Outlined).loadFont();

    IconManager::instance().registerProvider("MaterialRounded",
        std::shared_ptr<IconProvider>(&MaterialIconFactory::instance(Material::Style::Rounded),
        [](IconProvider*){}));
    success &= MaterialIconFactory::instance(Material::Style::Rounded).loadFont();

    IconManager::instance().registerProvider("MaterialSharp",
        std::shared_ptr<IconProvider>(&MaterialIconFactory::instance(Material::Style::Sharp),
        [](IconProvider*){}));
    success &= MaterialIconFactory::instance(Material::Style::Sharp).loadFont();

    // 这里可以添加更多图标提供者的注册和加载

    return success;
}

QIcon QIconKit::remixIcon(Remix::Icon icon, int size, const QColor& color) {
    return RemixIconFactory::instance().icon(icon, size, color);
}

QIcon QIconKit::lucideIcon(Lucide::Icon icon, int size, const QColor& color) {
    return LucideIconFactory::instance().icon(icon, size, color);
}

QIcon QIconKit::fontAwesomeIcon(FontAwesome::Icon icon, int size, const QColor& color) {
    return FontAwesomeIconFactory::instance().icon(icon, size, color);
}


QIcon QIconKit::materialFilledIcon(Material::Filled::Icon icon, int size, const QColor& color) {
    return MaterialIconFactory::instance(Material::Style::Filled).filledIcon(icon, size, color);
}

QIcon QIconKit::materialOutlinedIcon(Material::Outlined::Icon icon, int size, const QColor& color) {
    return MaterialIconFactory::instance(Material::Style::Outlined).outlinedIcon(icon, size, color);
}

QIcon QIconKit::materialRoundedIcon(Material::Rounded::Icon icon, int size, const QColor& color) {
    return MaterialIconFactory::instance(Material::Style::Rounded).roundedIcon(icon, size, color);
}

QIcon QIconKit::materialSharpIcon(Material::Sharp::Icon icon, int size, const QColor& color) {
    return MaterialIconFactory::instance(Material::Style::Sharp).sharpIcon(icon, size, color);
}


QIcon QIconKit::materialIcon(int iconCode, Material::Style style, int size, const QColor& color) {
    return MaterialIconFactory::instance(style).icon(iconCode, style, size, color);
}

} // namespace QtIcons