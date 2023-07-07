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
#include <QGraphicsEffect>

class BotBase : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	BotBase(int x, int y, qreal hpmax, qreal atk, qreal expgiven, QObject* parent=nullptr);
	bool attackableCheck();
	qreal attack(const QPointF& targ);
	void moveRound();
	void hurt(qreal damage);
	void endHurt();

	static QSoundEffect* sfxEnemyHurt;
	QGraphicsColorizeEffect *effHurted;
	QTimer* hurtTimer;

protected:
	qreal hpmax;
	qreal hp;
	qreal atk;
	int expWhenDie;
	QPixmap pic;
	int posx;
	int posy;

signals:
	void botDeath(const int& expWhenDie, int x, int y);
};

