#include "QStartupMenuWindow.h"
#include "QGameWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGameWindow* gameWindow = new QGameWindow();
    QStartupMenuWindow* menuWindow = new QStartupMenuWindow();
    menuWindow->connectToGameWindow(gameWindow);
    menuWindow->show();
    return a.exec();
}
