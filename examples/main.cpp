#include "mainwindow.h"
#include <QApplication>
#include <QIconKit/qiconkit.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 初始化图标库
    if (!QIconKit::QIconKit::initialize()) {
        qWarning() << "初始化图标库失败!";
    }

    MainWindow window;
    window.show();

    return QApplication::exec();
}