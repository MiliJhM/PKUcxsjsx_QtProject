#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QStartupMenuWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QFileDialog>
#include "QGameWindow.h"


class QStartupMenuWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::QStartupMenuWindow ui;
    size_t difficulty;
    

public:
    QStartupMenuWindow(QMainWindow* parent = nullptr);
    ~QStartupMenuWindow();

    void connectToGameWindow(QGameWindow* gw);


public slots:
    void changeDifficulty();
    void startNew();
    void loadGame();
    void startupCompleted(QGameWindow& mw);
    void reopen(QGameWindow& mw);

signals:
    void difficultyChanged(size_t diff);
    void newStarted(const int& difficulty);
    void gameLoaded(const QFile& binSL);
    
};
