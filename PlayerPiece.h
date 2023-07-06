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

	void moveTo(int x, int y);
	void hurt(qreal damage);
	void death();
	void attack();

private:


};
