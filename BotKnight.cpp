#include "BotKnight.h"

BotKnight::BotKnight(qreal hpmax, qreal atk, qreal expgiven, QObject* parent, BotBase* chessboard_[][8]) :BotBase(hpmax, atk, expgiven, parent), chessboard() {
    for (int i = 0; i < 8; i++) {
        chessboard[i] = chessboard_[i];
    }
    pic = QPixmap("./Images/BotKnight.png");
    setPixmap(pic);
    setScale(0.39);
}

bool BotKnight::attackableCheck(int x1, int y1)
{
    return (abs(posx - x1) == 1 && abs(posy - y1) == 2) || (abs(posx - x1) == 2 && abs(posy - y1) == 1) || (abs(posx-x1)<=1&&abs(posy-y1)<=1);
}

void BotKnight::moveRound(int x, int y) {
    int nowdist = abs(x - posx) + abs(y - posy);
    int diff[8][2] = { {1,2},{1,-2},{2,1},{2,-1},{-1,2},{-1,-2},{-2,1},{-2,-1} };
    int minx=posx, miny=posy, mind=nowdist;
    for (int i = 0; i < 8; i++)
    {
        int newx = posx + diff[i][0];
        int newy = posy + diff[i][1];
        if (newx>=0&&newx<8&&newy>=0&&newy<=8&&chessboard[newx][newy] == nullptr) {
            int newdist = abs(x - newx) + abs(y - newy);
            if (newdist <= mind) {
                mind = newdist;
                minx = newx;
                miny = newy;
            }
        }
    }
    moveToEffect(minx, miny);
    return;
}