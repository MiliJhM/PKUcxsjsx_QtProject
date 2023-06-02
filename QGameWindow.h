#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include "ui_QGameWindow.h"
#include <QVBoxLayout>
#include <QFile>
#include <QFileDialog>
#include <QLCDNumber>
#include "ChessBoard.h"

class QGameWindow :
    public QMainWindow
{
private:

    Ui::QGameWindow ui;
    ChessBoard* board;

public:
    QGameWindow(QWidget* parent = nullptr);

public slots:
    void newGameInit(const int& difficulty);
    
signals:
    void startupCompleted(const QGameWindow& a); // TODO��������źŴ���MenuWindow��ͬʱ���ò�����GameWindow������
};

