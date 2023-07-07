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

    void fireCd();

    int difficulty;

    PlayerPiece* player;
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
    BotBase* enemyGenerate(int& sum);
    void enemyDeathProcess(const int& expWhenDie, int x, int y);


    int killCounter = 0;

    int pesudoTime = 0;
    int enemyRound = 0;

    int normalRoundTime = 5;
    int eliteRoundTime = 3;
    int generateRoundTime = 10;

    void timerRun();
    void normalMoveRound();
    void eliteMoveRound();
    void generateRound();
    
    void win();
    void lose();

private:
    QSoundEffect* sfxMove;
    QGraphicsScene* main_sce;
    QGraphicsScene* end_sce;
    QGraphicsPixmapItem* m_background;
    QPushButton* pb_pause;
    QPushButton* pb_restart;
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

};

