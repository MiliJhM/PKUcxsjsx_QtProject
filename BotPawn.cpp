#include "BotPawn.h"

BotPawn::BotPawn(qreal hpmax, qreal atk, qreal expgiven, QObject* parent, BotBase* chessboard_[][8]) :BotBase(hpmax, atk, expgiven, parent), chessboard() {
    for (int i = 0; i < 8; i++) {
        chessboard[i] = chessboard_[i];
    }
    pic = QPixmap("./Images/BotPawn.png");
    setPixmap(pic);
    setScale(0.39);
}

bool BotPawn::attackableCheck(int x1, int y1)
{
    return (y1 == posy + 1 && abs(x1 - posx) == 1);
}

void BotPawn::moveRound(int x, int y) {
    int nowdist = abs(x - posx) + abs(y - posy);
    if (chessboard[posx][posy + 1] == nullptr&&posy<7) {
        int newx = posx;
        int newy = posy+1;
        int newdist = abs(x - newx) + abs(y - newy);
        if (newdist <= nowdist) {
            moveToEffect(newx, newy);
        }
    }
    return;
}