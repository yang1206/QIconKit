#ifndef QTWIDGETSAMPLE_H
#define QTWIDGETSAMPLE_H

#include <QWidget>
#include <QScrollArea>
#include <QIconKit/animated_icon.h>

class QtWidgetSample : public QWidget {
    Q_OBJECT
    
public:
    explicit QtWidgetSample(QWidget *parent = nullptr);
    
private slots:
    void startAllAnimations();
    void stopAllAnimations();
    void pauseAllAnimations();
    void resumeAllAnimations();
    
private:
    void setupUI();
    void addWidgetSamples();
    void addAnimationSamples();
    
    QScrollArea* m_scrollArea;
    QWidget* m_contentWidget;
    
    // 保存动画图标的引用，以便控制它们
    QList<QIconKit::AnimatedIcon*> m_animatedIcons;
};

#endif // QTWIDGETSAMPLE_H 