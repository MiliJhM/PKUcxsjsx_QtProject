#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QFileDialog>


class QStartupMenuWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::QStartupMenuWindow ui;
    size_t difficulty;
    

public:
    QStartupMenuWindow(QMainWindow* parent = nullptr);

    ~QStartupMenuWindow();



public slots:
    void changeDifficulty();
    void startNew();
    void loadGame();
    void startupCompleted();

signals:
    void difficultyChanged(size_t diff);
    void newStarted(const int& difficulty);
    void gameLoaded(const QFile& binSL);

};
