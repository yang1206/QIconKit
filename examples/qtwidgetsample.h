#ifndef QTWIDGETSAMPLE_H
#define QTWIDGETSAMPLE_H

#include <QWidget>
#include <QScrollArea>

class QtWidgetSample : public QWidget {
    Q_OBJECT
    
public:
    explicit QtWidgetSample(QWidget *parent = nullptr);
    
private:
    void setupUI();
    void addWidgetSamples();
    
    QScrollArea* m_scrollArea;
    QWidget* m_contentWidget;
};

#endif // QTWIDGETSAMPLE_H 