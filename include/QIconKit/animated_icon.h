#ifndef ANIMATED_ICON_H
#define ANIMATED_ICON_H

#include <QWidget>
#include <QIcon>
#include <QPropertyAnimation>
#include <QVariantAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QAbstractButton>
#include "QIconKit/QIconKit_export.h"

namespace QIconKit {

// 动画类型枚举
enum class AnimationType {
    Spin,       // 旋转动画
    Pulse,      // 脉冲效果（缩放）
    Bounce,     // 弹跳效果
    Shake,      // 摇晃效果
    Fade,       // 淡入淡出
    Blink,      // 闪烁效果
    Beat,       // 心跳效果
    Flip        // 翻转效果
};

// 动画参数结构
struct QICONKIT_EXPORT AnimationParams {
    int duration = 1000;           // 动画持续时间（毫秒）
    int loopCount = -1;            // 循环次数，-1表示无限循环
    bool autoStart = true;         // 是否自动开始动画
    qreal minScale = 0.8;          // 最小缩放比例（用于Pulse等动画）
    qreal maxScale = 1.2;          // 最大缩放比例
    qreal angle = 360.0;           // 旋转角度（用于Spin动画）
    qreal shakeAmount = 5.0;       // 摇晃幅度（用于Shake动画）
    qreal bounceFactor = 15.0;     // 弹跳系数（用于Bounce动画）
    qreal opacity = 0.3;           // 透明度参数（用于Fade/Blink动画）
};
class QICONKIT_EXPORT AnimatedIcon : public QWidget {
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
    Q_PROPERTY(qreal xOffset READ xOffset WRITE setXOffset)
    Q_PROPERTY(qreal yOffset READ yOffset WRITE setYOffset)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    explicit AnimatedIcon(const QIcon& icon,
                         AnimationType type = AnimationType::Spin,
                         const AnimationParams& params = AnimationParams(),
                         QWidget* parent = nullptr);
    ~AnimatedIcon() override;

    // 设置/获取图标
    void setIcon(const QIcon& icon);
    QIcon icon() const;

    // 设置/获取大小
    void setIconSize(const QSize& size);
    QSize iconSize() const;

    // 设置/获取颜色
    void setIconColor(const QColor& color);
    QColor iconColor() const;

    // 动画控制方法
    void start();
    void stop();
    void pause();
    void resume();
    bool isRunning() const;

    // 动画参数设置
    void setAnimationType(AnimationType type);
    void setAnimationParams(const AnimationParams& params);

    // 附加到按钮的方法
    void attachToButton(QAbstractButton* button);
    void detachFromButton();
    QAbstractButton* attachedButton() const;

    // 获取当前状态的图标
    QIcon currentIcon() const;

    // 创建特定的动画类型
    static AnimatedIcon* createSpinIcon(const QIcon& icon, const AnimationParams& params = AnimationParams(), QWidget* parent = nullptr);
    static AnimatedIcon* createPulseIcon(const QIcon& icon, const AnimationParams& params = AnimationParams(), QWidget* parent = nullptr);
    static AnimatedIcon* createBounceIcon(const QIcon& icon, const AnimationParams& params = AnimationParams(), QWidget* parent = nullptr);
    static AnimatedIcon* createShakeIcon(const QIcon& icon, const AnimationParams& params = AnimationParams(), QWidget* parent = nullptr);
    static AnimatedIcon* createFadeIcon(const QIcon& icon, const AnimationParams& params = AnimationParams(), QWidget* parent = nullptr);
    static AnimatedIcon* createBlinkIcon(const QIcon& icon, const AnimationParams& params = AnimationParams(), QWidget* parent = nullptr);
    static AnimatedIcon* createBeatIcon(const QIcon& icon, const AnimationParams& params = AnimationParams(), QWidget* parent = nullptr);
    static AnimatedIcon* createFlipIcon(const QIcon& icon, const AnimationParams& params = AnimationParams(), QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private slots:
    void updateAttachedButton();

private:
    // 属性读写方法
    qreal rotation() const;
    void setRotation(qreal rotation);

    qreal scale() const;
    void setScale(qreal scale);

    qreal xOffset() const;
    void setXOffset(qreal xOffset);

    qreal yOffset() const;
    void setYOffset(qreal yOffset);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    // 创建不同类型的动画
    void createAnimation();
    void createSpinAnimation();
    void createPulseAnimation();
    void createBounceAnimation();
    void createShakeAnimation();
    void createFadeAnimation();
    void createBlinkAnimation();
    void createBeatAnimation();
    void createFlipAnimation();

private:
    QIcon m_icon;
    QSize m_iconSize;
    QColor m_iconColor;
    AnimationType m_animationType;
    AnimationParams m_params;

    QAbstractAnimation* m_animation;  // 当前活动的动画

    // 变换属性
    qreal m_rotation;
    qreal m_scale;
    qreal m_xOffset;
    qreal m_yOffset;
    qreal m_opacity;

    QAbstractButton* m_attachedButton;
    QTimer* m_buttonUpdateTimer;
};

} // namespace QIconKit

#endif // ANIMATED_ICON_H 