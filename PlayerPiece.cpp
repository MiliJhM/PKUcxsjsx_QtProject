#include "PlayerPiece.h"

PlayerPiece::PlayerPiece(QObject *parent)
	: QObject(parent)
{
	QPixmap* playerPng = new QPixmap("./Images/PlayerPiece.png");
	setPixmap(*playerPng);
}

