#include "BotKing.h"

BotKing::BotKing(qreal hpmax, qreal atk, qreal expgiven, QObject* parent, BotBase* chessboard_[][8]) :BotBase(hpmax, atk, expgiven, parent), chessboard() {
    for (int i = 0; i < 8; i++) {
        chessboard[i] = chessboard_[i];
    }
    pic = QPixmap("./Images/BotKing.png");
    setPixmap(pic);
    setScale(0.39);
}

bool BotKing::attackableCheck(int x1, int y1)
{
    return (abs(x1 - posx) == 1) && (abs(y1 - posy) == 1);
}

void BotKing::moveRound(int x, int y) {
    int nowdist = abs(x - posx) + abs(y - posy);
    int diff[8][2] = { {1,1},{1,-1},{-1,1},{-1,-1},{1,0},{-1,0},{0,1},{0,-1} };
    int minx = posx, miny = posy, mind = nowdist;
    for (int i = 0; i < 8; i++)
    {
        for (int probe = 1;probe<=1; probe++) {
            int newx = posx + diff[i][0] * probe;
            int newy = posy + diff[i][1] * probe;
            if (newx >= 0 && newx < 8 && newy >= 0 && newy <= 8 && chessboard[newx][newy] == nullptr) {
                int newdist = abs(x - newx) + abs(y - newy);
                if (newdist <= mind) {
                    mind = newdist;
                    minx = newx;
                    miny = newy;
                }
            }
            else break;
        }
    }
    moveToEffect(minx, miny);
    return;
}