#include "QIconKit/animated_icon.h"
#include <QPainter>
#include <QTransform>
#include <QTimer>

namespace QIconKit {

AnimatedIcon::AnimatedIcon(const QIcon& icon, AnimationType type, const AnimationParams& params, QWidget* parent)
    : QWidget(parent)
    , m_icon(icon)
    , m_iconSize(24, 24)  // 默认大小
    , m_iconColor(Qt::black)
    , m_animationType(type)
    , m_params(params)
    , m_animation(nullptr)
    , m_rotation(0.0)
    , m_scale(1.0)
    , m_xOffset(0.0)
    , m_yOffset(0.0)
    , m_opacity(1.0)
    , m_attachedButton(nullptr)
    , m_buttonUpdateTimer(nullptr)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    
    createAnimation();
    
    // 创建按钮更新定时器
    m_buttonUpdateTimer = new QTimer(this);
    m_buttonUpdateTimer->setInterval(30); // 约33fps的更新频率
    connect(m_buttonUpdateTimer, &QTimer::timeout, this, &AnimatedIcon::updateAttachedButton);
    
    if (m_params.autoStart && m_animation) {
        m_animation->start();
    }
}

AnimatedIcon::~AnimatedIcon() {
    detachFromButton(); // 确保分离按钮
    if (m_animation) {
        m_animation->stop();
        delete m_animation;
    }
}

void AnimatedIcon::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    
    // 设置透明度
    painter.setOpacity(m_opacity);
    
    // 保存当前状态
    painter.save();
    
    // 移动到中心点
    painter.translate(rect().center());
    
    // 应用变换
    painter.rotate(m_rotation);
    painter.scale(m_scale, m_scale);
    painter.translate(m_xOffset, m_yOffset);
    
    // 绘制图标
    QRect iconRect(-m_iconSize.width() / 2, -m_iconSize.height() / 2, 
                  m_iconSize.width(), m_iconSize.height());
    m_icon.paint(&painter, iconRect, Qt::AlignCenter, QIcon::Normal, QIcon::On);
    
    // 恢复状态
    painter.restore();
}

QSize AnimatedIcon::sizeHint() const {
    return m_iconSize;
}

QSize AnimatedIcon::minimumSizeHint() const {
    return m_iconSize;
}

void AnimatedIcon::setIcon(const QIcon& icon) {
    m_icon = icon;
    update();
}

QIcon AnimatedIcon::icon() const {
    return m_icon;
}

void AnimatedIcon::setIconSize(const QSize& size) {
    m_iconSize = size;
    updateGeometry();
    update();
}

QSize AnimatedIcon::iconSize() const {
    return m_iconSize;
}

void AnimatedIcon::setIconColor(const QColor& color) {
    m_iconColor = color;
    update();
}

QColor AnimatedIcon::iconColor() const {
    return m_iconColor;
}

// 实现属性读写方法
qreal AnimatedIcon::rotation() const { return m_rotation; }
void AnimatedIcon::setRotation(qreal rotation) { 
    m_rotation = rotation; 
    update(); 
}

qreal AnimatedIcon::scale() const { return m_scale; }
void AnimatedIcon::setScale(qreal scale) { 
    m_scale = scale; 
    update(); 
}

qreal AnimatedIcon::xOffset() const { return m_xOffset; }
void AnimatedIcon::setXOffset(qreal xOffset) { 
    m_xOffset = xOffset; 
    update(); 
}

qreal AnimatedIcon::yOffset() const { return m_yOffset; }
void AnimatedIcon::setYOffset(qreal yOffset) { 
    m_yOffset = yOffset; 
    update(); 
}

qreal AnimatedIcon::opacity() const { return m_opacity; }
void AnimatedIcon::setOpacity(qreal opacity) { 
    m_opacity = opacity; 
    update(); 
}

// 动画控制方法
void AnimatedIcon::start() {
    if (m_animation) {
        m_animation->start();
        if (m_attachedButton) {
            m_buttonUpdateTimer->start();
        }
    }
}

void AnimatedIcon::stop() {
    if (m_animation) {
        m_animation->stop();
        if (m_attachedButton) {
            m_buttonUpdateTimer->stop();
            // 重置按钮图标到初始状态
            m_rotation = 0.0;
            m_scale = 1.0;
            m_xOffset = 0.0;
            m_yOffset = 0.0;
            m_opacity = 1.0;
            updateAttachedButton();
        } else {
            // 重置属性
            m_rotation = 0.0;
            m_scale = 1.0;
            m_xOffset = 0.0;
            m_yOffset = 0.0;
            m_opacity = 1.0;
            update();
        }
    }
}

void AnimatedIcon::pause() {
    if (m_animation) {
        m_animation->pause();
        if (m_attachedButton) {
            m_buttonUpdateTimer->stop();
        }
    }
}

void AnimatedIcon::resume() {
    if (m_animation) {
        m_animation->resume();
        if (m_attachedButton && isRunning()) {
            m_buttonUpdateTimer->start();
        }
    }
}

bool AnimatedIcon::isRunning() const {
    return m_animation && m_animation->state() == QAbstractAnimation::Running;
}

void AnimatedIcon::setAnimationType(AnimationType type) {
    if (m_animationType == type) {
        return;
    }
    
    m_animationType = type;
    
    // 删除现有动画
    if (m_animation) {
        m_animation->stop();
        delete m_animation;
        m_animation = nullptr;
    }
    
    createAnimation();
    
    if (m_params.autoStart && m_animation) {
        m_animation->start();
    }
}

void AnimatedIcon::setAnimationParams(const AnimationParams& params) {
    m_params = params;
    
    // 重新创建动画
    if (m_animation) {
        m_animation->stop();
        delete m_animation;
        m_animation = nullptr;
    }
    
    createAnimation();
    
    if (m_params.autoStart && m_animation) {
        m_animation->start();
    }
}

// 创建不同类型的动画实例的静态方法
AnimatedIcon* AnimatedIcon::createSpinIcon(const QIcon& icon, const AnimationParams& params, QWidget* parent) {
    return new AnimatedIcon(icon, AnimationType::Spin, params, parent);
}

AnimatedIcon* AnimatedIcon::createPulseIcon(const QIcon& icon, const AnimationParams& params, QWidget* parent) {
    return new AnimatedIcon(icon, AnimationType::Pulse, params, parent);
}

AnimatedIcon* AnimatedIcon::createBounceIcon(const QIcon& icon, const AnimationParams& params, QWidget* parent) {
    return new AnimatedIcon(icon, AnimationType::Bounce, params, parent);
}

AnimatedIcon* AnimatedIcon::createShakeIcon(const QIcon& icon, const AnimationParams& params, QWidget* parent) {
    return new AnimatedIcon(icon, AnimationType::Shake, params, parent);
}

AnimatedIcon* AnimatedIcon::createFadeIcon(const QIcon& icon, const AnimationParams& params, QWidget* parent) {
    return new AnimatedIcon(icon, AnimationType::Fade, params, parent);
}

AnimatedIcon* AnimatedIcon::createBlinkIcon(const QIcon& icon, const AnimationParams& params, QWidget* parent) {
    return new AnimatedIcon(icon, AnimationType::Blink, params, parent);
}

AnimatedIcon* AnimatedIcon::createBeatIcon(const QIcon& icon, const AnimationParams& params, QWidget* parent) {
    return new AnimatedIcon(icon, AnimationType::Beat, params, parent);
}

AnimatedIcon* AnimatedIcon::createFlipIcon(const QIcon& icon, const AnimationParams& params, QWidget* parent) {
    return new AnimatedIcon(icon, AnimationType::Flip, params, parent);
}

// 创建动画的方法
void AnimatedIcon::createAnimation() {
    switch (m_animationType) {
        case AnimationType::Spin:
            createSpinAnimation();
            break;
        case AnimationType::Pulse:
            createPulseAnimation();
            break;
        case AnimationType::Bounce:
            createBounceAnimation();
            break;
        case AnimationType::Shake:
            createShakeAnimation();
            break;
        case AnimationType::Fade:
            createFadeAnimation();
            break;
        case AnimationType::Blink:
            createBlinkAnimation();
            break;
        case AnimationType::Beat:
            createBeatAnimation();
            break;
        case AnimationType::Flip:
            createFlipAnimation();
            break;
    }
}

// 实现各种动画类型
void AnimatedIcon::createSpinAnimation() {
    QPropertyAnimation* spinAnimation = new QPropertyAnimation(this, "rotation");
    spinAnimation->setStartValue(0.0);
    spinAnimation->setEndValue(m_params.angle);
    spinAnimation->setDuration(m_params.duration);
    spinAnimation->setLoopCount(m_params.loopCount);
    spinAnimation->setEasingCurve(QEasingCurve::Linear);
    
    m_animation = spinAnimation;
}

void AnimatedIcon::createPulseAnimation() {
    QPropertyAnimation* pulseAnimation = new QPropertyAnimation(this, "scale");
    pulseAnimation->setStartValue(1.0);
    pulseAnimation->setKeyValueAt(0.5, m_params.maxScale);
    pulseAnimation->setEndValue(1.0);
    pulseAnimation->setDuration(m_params.duration);
    pulseAnimation->setLoopCount(m_params.loopCount);
    pulseAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    
    m_animation = pulseAnimation;
}

void AnimatedIcon::createBounceAnimation() {
    QPropertyAnimation* bounceAnimation = new QPropertyAnimation(this, "yOffset");
    bounceAnimation->setStartValue(0.0);
    bounceAnimation->setKeyValueAt(0.5, -m_params.bounceFactor);
    bounceAnimation->setEndValue(0.0);
    bounceAnimation->setDuration(m_params.duration);
    bounceAnimation->setLoopCount(m_params.loopCount);
    bounceAnimation->setEasingCurve(QEasingCurve::OutBounce);
    
    m_animation = bounceAnimation;
}

void AnimatedIcon::createShakeAnimation() {
    QSequentialAnimationGroup* shakeGroup = new QSequentialAnimationGroup(this);
    
    // 左右摇晃序列
    for (int i = 0; i < 3; i++) {
        QPropertyAnimation* toRight = new QPropertyAnimation(this, "xOffset");
        toRight->setStartValue(0.0);
        toRight->setEndValue(m_params.shakeAmount);
        toRight->setDuration(m_params.duration / 6);
        toRight->setEasingCurve(QEasingCurve::InOutQuad);
        
        QPropertyAnimation* toLeft = new QPropertyAnimation(this, "xOffset");
        toLeft->setStartValue(m_params.shakeAmount);
        toLeft->setEndValue(-m_params.shakeAmount);
        toLeft->setDuration(m_params.duration / 3);
        toLeft->setEasingCurve(QEasingCurve::InOutQuad);
        
        QPropertyAnimation* toCenter = new QPropertyAnimation(this, "xOffset");
        toCenter->setStartValue(-m_params.shakeAmount);
        toCenter->setEndValue(0.0);
        toCenter->setDuration(m_params.duration / 6);
        toCenter->setEasingCurve(QEasingCurve::InOutQuad);
        
        shakeGroup->addAnimation(toRight);
        shakeGroup->addAnimation(toLeft);
        shakeGroup->addAnimation(toCenter);
    }
    
    shakeGroup->setLoopCount(m_params.loopCount);
    m_animation = shakeGroup;
}

void AnimatedIcon::createFadeAnimation() {
    QPropertyAnimation* fadeAnimation = new QPropertyAnimation(this, "opacity");
    fadeAnimation->setStartValue(1.0);
    fadeAnimation->setEndValue(m_params.opacity);
    fadeAnimation->setDuration(m_params.duration / 2);
    fadeAnimation->setLoopCount(m_params.loopCount);
    fadeAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    
    QPropertyAnimation* fadeInAnimation = new QPropertyAnimation(this, "opacity");
    fadeInAnimation->setStartValue(m_params.opacity);
    fadeInAnimation->setEndValue(1.0);
    fadeInAnimation->setDuration(m_params.duration / 2);
    fadeInAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    
    QSequentialAnimationGroup* fadeGroup = new QSequentialAnimationGroup(this);
    fadeGroup->addAnimation(fadeAnimation);
    fadeGroup->addAnimation(fadeInAnimation);
    fadeGroup->setLoopCount(m_params.loopCount);
    
    m_animation = fadeGroup;
}

void AnimatedIcon::createBlinkAnimation() {
    QPropertyAnimation* hideAnimation = new QPropertyAnimation(this, "opacity");
    hideAnimation->setStartValue(1.0);
    hideAnimation->setEndValue(0.0);
    hideAnimation->setDuration(100);
    
    QPropertyAnimation* showAnimation = new QPropertyAnimation(this, "opacity");
    showAnimation->setStartValue(0.0);
    showAnimation->setEndValue(1.0);
    showAnimation->setDuration(100);
    
    QSequentialAnimationGroup* blinkGroup = new QSequentialAnimationGroup(this);
    blinkGroup->addAnimation(hideAnimation);
    blinkGroup->addAnimation(showAnimation);
    
    QSequentialAnimationGroup* fullBlinkGroup = new QSequentialAnimationGroup(this);
    fullBlinkGroup->addAnimation(blinkGroup);
    
    // 添加暂停以控制闪烁频率
    QParallelAnimationGroup* pauseGroup = new QParallelAnimationGroup();
    QPropertyAnimation* pauseAnimation = new QPropertyAnimation(this, "opacity");
    pauseAnimation->setStartValue(1.0);
    pauseAnimation->setEndValue(1.0);
    pauseAnimation->setDuration(m_params.duration - 200);
    pauseGroup->addAnimation(pauseAnimation);
    
    fullBlinkGroup->addAnimation(pauseGroup);
    fullBlinkGroup->setLoopCount(m_params.loopCount);
    
    m_animation = fullBlinkGroup;
}

void AnimatedIcon::createBeatAnimation() {
    QParallelAnimationGroup* beatGroup = new QParallelAnimationGroup(this);
    
    // 缩放动画
    QPropertyAnimation* scaleAnimation = new QPropertyAnimation(this, "scale");
    scaleAnimation->setStartValue(1.0);
    scaleAnimation->setKeyValueAt(0.1, m_params.maxScale);
    scaleAnimation->setKeyValueAt(0.2, m_params.maxScale * 0.9);
    scaleAnimation->setKeyValueAt(0.3, m_params.maxScale);
    scaleAnimation->setEndValue(1.0);
    scaleAnimation->setDuration(m_params.duration);
    scaleAnimation->setEasingCurve(QEasingCurve::OutCubic);
    
    beatGroup->addAnimation(scaleAnimation);
    beatGroup->setLoopCount(m_params.loopCount);
    
    m_animation = beatGroup;
}

void AnimatedIcon::createFlipAnimation() {
    QPropertyAnimation* flipAnimation = new QPropertyAnimation(this, "scale");
    flipAnimation->setDuration(m_params.duration);
    flipAnimation->setLoopCount(m_params.loopCount);
    flipAnimation->setKeyValueAt(0.0, 1.0);   // 开始：正常
    flipAnimation->setKeyValueAt(0.25, 0.0);  // 1/4：消失（X轴方向）
    flipAnimation->setKeyValueAt(0.5, -1.0);  // 1/2：翻转
    flipAnimation->setKeyValueAt(0.75, 0.0);  // 3/4：消失（X轴方向） 
    flipAnimation->setKeyValueAt(1.0, 1.0);   // 结束：回到正常
    flipAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    
    m_animation = flipAnimation;
}

void AnimatedIcon::attachToButton(QAbstractButton* button) {
    // 先分离之前可能附加的按钮
    if (m_attachedButton) {
        detachFromButton();
    }
    
    m_attachedButton = button;
    
    if (m_attachedButton) {
        // 保存按钮原始尺寸策略
        m_attachedButton->setIconSize(m_iconSize);
        
        // 更新按钮图标
        updateAttachedButton();
        
        // 如果动画正在运行，启动定时器
        if (isRunning()) {
            m_buttonUpdateTimer->start();
        }
    }
}

void AnimatedIcon::detachFromButton() {
    if (m_attachedButton) {
        m_buttonUpdateTimer->stop();
        m_attachedButton = nullptr;
    }
}

QAbstractButton* AnimatedIcon::attachedButton() const {
    return m_attachedButton;
}

QIcon AnimatedIcon::currentIcon() const {
    // 创建一个临时像素图来捕获当前状态
    QPixmap pixmap(m_iconSize);
    pixmap.fill(Qt::transparent);
    
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    
    // 设置透明度
    painter.setOpacity(m_opacity);
    
    // 保存当前状态
    painter.save();
    
    // 移动到中心点
    painter.translate(pixmap.rect().center());
    
    // 应用变换
    painter.rotate(m_rotation);
    painter.scale(m_scale, m_scale);
    painter.translate(m_xOffset, m_yOffset);
    
    // 绘制图标
    QRect iconRect(-m_iconSize.width() / 2, -m_iconSize.height() / 2, 
                  m_iconSize.width(), m_iconSize.height());
    m_icon.paint(&painter, iconRect, Qt::AlignCenter, QIcon::Normal, QIcon::On);
    
    // 恢复状态
    painter.restore();
    
    return QIcon(pixmap);
}

void AnimatedIcon::updateAttachedButton() {
    if (m_attachedButton) {
        m_attachedButton->setIcon(currentIcon());
    }
}

} // namespace QIconKit 