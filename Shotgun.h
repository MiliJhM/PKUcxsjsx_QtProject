#pragma once


#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QSoundEffect>
#include <QUrl>
#include <QtMath>
#include <QRandomGenerator>
#include "PlayerPiece.h"
#include "Bullet.h"
class Shotgun : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	Shotgun(PlayerPiece* pl, QGraphicsScene* sce, QObject* parent);

	void updatePos();
	void rotateToCursor(const QPointF& target);
	void fire(qreal damage, const QPointF& target, int bulletcnt, int penetration, qreal spread);

protected:
	QGraphicsScene* sce;
	PlayerPiece* ptr_player;
	QPixmap* px;
	QPixmap* px_rotated;
	QSoundEffect* sfxFire;
};

