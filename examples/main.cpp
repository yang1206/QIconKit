#include "mainwindow.h"
#include <QApplication>
#include <QtIcons/qticons.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 初始化图标库
    if (!QtIcons::QtIcons::initialize()) {
        qWarning() << "初始化图标库失败!";
    }

    MainWindow window;
    window.show();

    return QApplication::exec();
}