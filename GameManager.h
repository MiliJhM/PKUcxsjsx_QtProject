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
    GameManager(const QString& dir_archive = NULL);
    GameManager(const int& difficulty);
    void returnToMenu();

signals:
    void gameEnd();
    void restart();

protected:
    int difficulty;

    PlayerPiece* player;
    int playerx, playery;

    qreal playerHp;
    qreal playerHpmax;
    qreal playerDef;
    qreal playerAtk;
    qreal playerDodge;
    qreal playerScatterAngle;
    void setHpPrinter();

    BotBase* chessboard[8][8]{}; // 左上角视为0，0；右上角视为7，0；

    int level;
    int expnow;
    int expneed;
    void expGet(int x);
    void levelCheck();
    void levelUp();
    QList<int> rougeGenerator();
    void setExpPrinter();

    int enemyGenCount;
    void enemyGenerate();
    
    int pesudoTime;
    void normalMoveRound();
    void eliteMoveRound();
    void generateRound();
    
    void win();
    void lose();

private:
    QGraphicsScene* main_sce;
    QGraphicsScene* end_sce;
    QTimer* main_timer;
    QGraphicsPixmapItem* m_background;
    QPushButton* pb_pause;
    QPushButton* pb_restart;
};

