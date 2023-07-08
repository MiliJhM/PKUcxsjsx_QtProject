#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEffect>
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

#include <iostream>
#include <sstream>
#include <string>

#include "BotBase.h"
#include "BotBishop.h"
#include "BotKing.h"
#include "BotKnight.h"
#include "BotPawn.h"
#include "BotQueen.h"
#include "BotRook.h"
#include "PlayerPiece.h"
#include "Shotgun.h"

class GameManager :
    public QGraphicsView
{
    Q_OBJECT

public:
    GameManager(const QString& dir_archive = NULL);
    GameManager(const int& difficulty, QWidget* parent);
    void returnToMenu();

signals:
    void gameEnd();
    void restart();

protected:
    QTimer* mainTimer;
    QTimer* fireTimer;

    bool mouseFlag = 0;
    bool fireFlag = 0;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void playerMove(int newX, int newY);
    void weaponPosUpd();
    void fireCd();

    int difficulty;


    PlayerPiece* player;
    QPropertyAnimation* animation;
    Shotgun* weapon;
    int playerx, playery;

    qreal playerHp;
    qreal playerHpmax;
    qreal playerDef;
    qreal playerAtk;
    qreal playerDodge;
    qreal playerScatterAngle;
    int playerBulletNum;
    void setHpPrinter();
    bool playerMoveCheck(int newX, int newY);
    BotBase* chessboard[8][8]{}; // 左上角视为0，0；右上角视为7，0；

    int level;
    int expnow;
    int expneed;
    void expGet(const int& x);
    void levelCheck();
    void levelUp();
    // QList<int> rougeGenerator();
    void setExpPrinter();

    void setAllPrinter();

    int enemyGenCount;
    BotBase* enemyGenerate(const int& kind);
    void enemyDeathProcess(const int& expWhenDie, int x, int y);


    int killCounter = 0;

    int pesudoTime = 0;
    int enemyStrength = 1;

    int RoundTime;

    void timerRun();
    void moveRound();
    void generateRound();
    void enemyMove(int x, int y, int newx, int newy);
    void win();
    void lose();

private:
    QSoundEffect* sfxMove;
    QGraphicsScene* main_sce;
    QGraphicsScene* end_sce;
    QGraphicsPixmapItem* m_background;
    QGraphicsPixmapItem* end_m_background;
    QPushButton* pb_pause;
    QPushButton* pb_restart;
    QPushButton* pb_pause_end;
    QPushButton* pb_restart_end;
    QLabel* lb_end;
    QGraphicsOpacityEffect* effReadyToMove;
    QGraphicsColorizeEffect* effHurted;
    
    QLabel* lb_hpnow;
    QLabel* lb_def;
    QLabel* lb_dodge;
    QLabel* lb_scAngle;
    QLabel* lb_atk;
    QLabel* lb_bulletNum;
    QLabel* lb_level;
    QLabel* lb_expnow;
    QLabel* lb_killCounter;
    QLabel* lb_diff;
    QPointF targKeeper;
};

