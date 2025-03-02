//
// Created by Yang1206 on 2025/3/2.
//

#ifndef QTICONS_H
#define QTICONS_H

#include "icon_factories.h"
#include "QIconKit/QIconKit_export.h"


namespace QIconKit {

class QICONKIT_EXPORT QIconKit {
public:
    // 初始化库，加载所有内置字体
    static bool initialize();

    // RemixIcon图标
    static QIcon remixIcon(Remix::Icon icon, int size = 16, const QColor& color = QColor(0, 0, 0));

    // LucideIcon图标
    static QIcon lucideIcon(Lucide::Icon icon, int size = 16, const QColor& color = QColor(0, 0, 0));

    // FontAwesome图标
    static QIcon fontAwesomeIcon(FontAwesome::Icon icon, int size = 16, const QColor& color = QColor(0, 0, 0));

    // Material Icons - 填充样式
    static QIcon materialFilledIcon(Material::Filled::Icon icon, int size = 24, const QColor& color = Qt::black);

    // Material Icons - 轮廓样式
    static QIcon materialOutlinedIcon(Material::Outlined::Icon icon, int size = 24, const QColor& color = Qt::black);

    // Material Icons - 圆角样式
    static QIcon materialRoundedIcon(Material::Rounded::Icon icon, int size = 24, const QColor& color = Qt::black);

    // Material Icons - 尖角样式
    static QIcon materialSharpIcon(Material::Sharp::Icon icon, int size = 24, const QColor& color = Qt::black);

    // 通用方法 - 根据变体类型获取Material图标
    static QIcon materialIcon(int iconCode, Material::Style style = Material::Style::Filled, int size = 24, const QColor& color = Qt::black);

    // 这里可以添加更多图标类型的方法...
};

} // namespace QtIcons

#endif //QTICONS_H