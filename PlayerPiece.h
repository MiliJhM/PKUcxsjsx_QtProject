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
	int spd; // ���ÿ��spd����bot����һ�غϣ����Ƿ���GameManager��

	void moveTo(int x, int y);
	void hurt(qreal damage);
	void death();
	void attack();

};
