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


class PlayerPiece  : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
	Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
	PlayerPiece(QObject *parent=nullptr);

	void hurt(qreal damage);
	void endHurt();
	void death();

signals:
	void playerHurt();
	void playerDeath();

protected:
	QTimer* hurtTimer;
	QSoundEffect* sfxHurted;
	QGraphicsColorizeEffect* effHurt;

};
