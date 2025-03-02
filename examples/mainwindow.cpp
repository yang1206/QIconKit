#include "mainwindow.h"
#include <QTabWidget>
#include <QtIcons/qticons.h>
#include "qtwidgetsample.h"
#include "iconbrowser.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_tabWidget = new QTabWidget(this);
    setCentralWidget(m_tabWidget);

    // 添加Qt控件示例标签页
    QtWidgetSample* widgetSample = new QtWidgetSample();
    m_tabWidget->addTab(widgetSample, QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::AppsLine, 16), "Qt控件示例");

    // 添加图标浏览器标签页
    IconBrowser* iconBrowser = new IconBrowser();
    m_tabWidget->addTab(iconBrowser, QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::GridFill, 16), "图标浏览器");

    // 设置窗口属性
    setWindowTitle("QtIcons by Yang1206");
    setWindowIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::AppsLine, 32));
    resize(900, 700);
}