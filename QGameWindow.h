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
    Q_OBJECT
private:

    Ui::QGameWindow ui;
    ChessBoard* board;

public:
    QGameWindow(QWidget* parent = nullptr);

public slots:
    void newGameInit(const int& difficulty);
    void loadGame(const QFile& binSL);
    void pause();
    void exitToMenu();
    void saveSL();
    
signals:
    void startupCompleted(QGameWindow& a);
    void menuReopen(QGameWindow& a);

};

