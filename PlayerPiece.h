#pragma once

#include <QObject>
#include <QVector2D>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QFont>
#include <QPixmap>
#include <QTimer>
#include <QMovie>
#include <QSoundEffect>
#include <QUrl>


class PlayerPiece  : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	PlayerPiece(QObject *parent=nullptr);

	qreal hp;
	qreal hpmax;
	qreal def;
	qreal atk;
	qreal dodge;
	int spd; // 玩家每走spd步，bot运行一回合？考虑放入GameManager中

	void moveTo(int x, int y);
	void hurt(qreal damage);
	void death();
	void attack();

};
