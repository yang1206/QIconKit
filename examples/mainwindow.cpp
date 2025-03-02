#include "mainwindow.h"
#include <QTabWidget>
#include <QIconKit/qiconkit.h>
#include "qtwidgetsample.h"
#include "iconbrowser.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_tabWidget = new QTabWidget(this);
    setCentralWidget(m_tabWidget);

    // 添加Qt控件示例标签页
    QtWidgetSample* widgetSample = new QtWidgetSample();
    m_tabWidget->addTab(widgetSample, QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::AppsLine, 16), "Qt控件示例");

    // 添加图标浏览器标签页
    IconBrowser* iconBrowser = new IconBrowser();
    m_tabWidget->addTab(iconBrowser, QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::GridFill, 16), "图标浏览器");

    // 设置窗口属性
    setWindowTitle("QIconKit by Yang1206");
    setWindowIcon(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::AppsLine, 32));
    resize(900, 700);
}