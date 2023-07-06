#pragma once
#include <QWidget>

#include "StartMenuNew.h"
#include "GameManager.h"

class GameWidgetNew :
    public QWidget
{
    Q_OBJECT

public:
    GameWidgetNew(QWidget* parent = nullptr);
    void setDiff(int diff);
    void initMenu();
    void initGameMan();
    void startGameMan();
    void gameEnd();




private:
    StartMenuNew* ptr_startMenu;
    GameManager* ptr_gameMan;

    int gameDiff = 1;

    

};

