#pragma once
#include "BotBase.h"
class BotKnight :
    public BotBase
{
public:
    BotKnight(qreal hpmax, qreal atk, qreal expgiven, QObject* parent, BotBase* chessboard_[][8]);
    bool attacked = 0;
    BotBase** chessboard[8];

    bool posIsNull(int x, int y) {
        return chessboard[x][y] == nullptr;
    }

    virtual bool attackableCheck(int x1, int y1);

    virtual void moveRound(int x1, int y1);
};

