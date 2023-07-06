#pragma once
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


class BotBase : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	BotBase(QObject* parent=nullptr);
	bool attackableCheck();
	void attack();
	void moveRound();
	void hurt(qreal damage);

protected:
	qreal hpmax;
	qreal hp;
	qreal atk;
	int expWhenDie;
	QImage pic;

signals:
	void botDeath();
};

