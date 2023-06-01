#include "QStartupMenuWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStartupMenuWindow* w = new QStartupMenuWindow();
    w->show();
    return a.exec();
}
