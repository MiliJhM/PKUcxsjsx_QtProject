#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QTimer>
#include <QList>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QSettings>
#include <QFontDatabase>
#include <QApplication>
#include <QSoundEffect>

#include "BotBase.h"
#include "PlayerPiece.h"

class GameManager :
    public QGraphicsView
{
    Q_OBJECT

public:
    GameManager();
    void pauseGame();
    void continueGame();


protected:
    int difficulty;

    PlayerPiece* player;
    void setHpPrinter();

    int level;
    int expnow;
    int expneed;
    void levelCheck();
    void levelUp();
    QList<int> rougeGenerator();
    void setExpPrinter();

    void enemyGenerate();
    
    int pesudoTime;
    void normalMoveRound();
    void eliteMoveRound();
    void generateRound();
    
    void win();
    void lose();
};

