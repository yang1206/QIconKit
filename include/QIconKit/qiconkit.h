//
// Created by Yang1206 on 2025/3/2.
//

#ifndef QTICONS_H
#define QTICONS_H

#include "icon_factories.h"
#include "animated_icon.h"
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


     // 创建动画图标的方法
    static AnimatedIcon* createAnimatedIcon(const QIcon& icon,
                                          AnimationType type = AnimationType::Spin,
                                          const AnimationParams& params = AnimationParams(),
                                          QWidget* parent = nullptr);

    // RemixIcon动画图标
    static AnimatedIcon* createAnimatedRemixIcon(Remix::Icon icon,
                                               AnimationType type = AnimationType::Spin,
                                               int size = 16,
                                               const QColor& color = QColor(0, 0, 0),
                                               const AnimationParams& params = AnimationParams(),
                                               QWidget* parent = nullptr);

    // LucideIcon动画图标
    static AnimatedIcon* createAnimatedLucideIcon(Lucide::Icon icon,
                                                AnimationType type = AnimationType::Spin,
                                                int size = 16,
                                                const QColor& color = QColor(0, 0, 0),
                                                const AnimationParams& params = AnimationParams(),
                                                QWidget* parent = nullptr);

    // FontAwesome动画图标
    static AnimatedIcon* createAnimatedFontAwesomeIcon(FontAwesome::Icon icon,
                                                    AnimationType type = AnimationType::Spin,
                                                    int size = 16,
                                                    const QColor& color = QColor(0, 0, 0),
                                                    const AnimationParams& params = AnimationParams(),
                                                    QWidget* parent = nullptr);

    // Material动画图标 - 填充样式
    static AnimatedIcon* createAnimatedMaterialFilledIcon(Material::Filled::Icon icon,
                                                      AnimationType type = AnimationType::Spin,
                                                      int size = 24,
                                                      const QColor& color = Qt::black,
                                                      const AnimationParams& params = AnimationParams(),
                                                      QWidget* parent = nullptr);

    // Material动画图标 - 轮廓样式
    static AnimatedIcon* createAnimatedMaterialOutlinedIcon(Material::Outlined::Icon icon,
                                                      AnimationType type = AnimationType::Spin,
                                                      int size = 24,
                                                      const QColor& color = Qt::black,
                                                      const AnimationParams& params = AnimationParams(),
                                                      QWidget* parent = nullptr);

    // Material动画图标 - 圆角样式
    static AnimatedIcon* createAnimatedMaterialRoundedIcon(Material::Rounded::Icon icon,
                                                      AnimationType type = AnimationType::Spin,
                                                      int size = 24,
                                                      const QColor& color = Qt::black,
                                                      const AnimationParams& params = AnimationParams(),
                                                      QWidget* parent = nullptr);

    // Material动画图标 - 尖角样式
    static AnimatedIcon* createAnimatedMaterialSharpIcon(Material::Sharp::Icon icon,
                                                      AnimationType type = AnimationType::Spin,
                                                      int size = 24,
                                                      const QColor& color = Qt::black,
                                                      const AnimationParams& params = AnimationParams(),
                                                      QWidget* parent = nullptr);

    // 通用方法 - 根据变体类型获取Material图标
    static AnimatedIcon* createAnimatedMaterialIcon(int iconCode,
                                                      Material::Style style = Material::Style::Filled,
                                                      int size = 24,
                                                      const QColor& color = Qt::black,
                                                      const AnimationParams& params = AnimationParams(),
                                                      QWidget* parent = nullptr);

};

} // namespace QtIcons

#define RemixIcon(icon, ...) QIconKit::QIconKit::remixIcon(QIconKit::Remix::icon, ##__VA_ARGS__)
#define LucideIcon(icon, ...) QIconKit::QIconKit::lucideIcon(QIconKit::Lucide::icon, ##__VA_ARGS__)
#define FontAwesomeIcon(icon, ...) QIconKit::QIconKit::fontAwesomeIcon(QIconKit::FontAwesome::icon, ##__VA_ARGS__)
#define MaterialFilledIcon(icon, ...) QIconKit::QIconKit::materialFilledIcon(QIconKit::Material::Filled::icon, ##__VA_ARGS__)
#define MaterialOutlinedIcon(icon, ...) QIconKit::QIconKit::materialOutlinedIcon(QIconKit::Material::Outlined::icon, ##__VA_ARGS__)
#define MaterialRoundedIcon(icon, ...) QIconKit::QIconKit::materialRoundedIcon(QIconKit::Material::Rounded::icon, ##__VA_ARGS__)
#define MaterialSharpIcon(icon, ...) QIconKit::QIconKit::materialSharpIcon(QIconKit::Material::Sharp::icon, ##__VA_ARGS__)
#define AnimatedRemixIcon(icon, ...) QIconKit::QIconKit::createAnimatedRemixIcon(QIconKit::Remix::icon, ##__VA_ARGS__)
#define AnimatedLucideIcon(icon, ...) QIconKit::QIconKit::createAnimatedLucideIcon(QIconKit::Lucide::icon, ##__VA_ARGS__)
#define AnimatedFontAwesomeIcon(icon, ...) QIconKit::QIconKit::createAnimatedFontAwesomeIcon(QIconKit::FontAwesome::icon, ##__VA_ARGS__)
#define AnimatedMaterialFilledIcon(icon, ...) QIconKit::QIconKit::createAnimatedMaterialFilledIcon(QIconKit::Material::Filled::icon, ##__VA_ARGS__)
#define AnimatedMaterialOutlinedIcon(icon, ...) QIconKit::QIconKit::createAnimatedMaterialOutlinedIcon(QIconKit::Material::Outlined::icon, ##__VA_ARGS__)
#define AnimatedMaterialRoundedIcon(icon, ...) QIconKit::QIconKit::createAnimatedMaterialRoundedIcon(QIconKit::Material::Rounded::icon, ##__VA_ARGS__)
#define AnimatedMaterialSharpIcon(icon, ...) QIconKit::QIconKit::createAnimatedMaterialSharpIcon(QIconKit::Material::Sharp::icon, ##__VA_ARGS__)
#define AnimatedMaterialIcon(icon, ...) QIconKit::QIconKit::createAnimatedMaterialIcon(QIconKit::Material::icon, ##__VA_ARGS__)

#endif //QTICONS_H