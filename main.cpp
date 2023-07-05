#include "GameWidgetNew.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidgetNew* gmWidget = new GameWidgetNew;
    gmWidget->show();
    return a.exec();
}
