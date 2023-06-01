#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include <QPushButton>
#include <QVBoxLayout>

class QStartupMenuWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::QStartupMenuWindow ui;
    QPushButton* startButton;
    QPushButton* difficultyButton;
    QLCDNumber* difficultyDisplayer;
    size_t difficulty;
    

public:
    QStartupMenuWindow(QMainWindow* parent = nullptr);

    ~QStartupMenuWindow();



public slots:

    void changeDifficulty();


signals:
    void difficultyChanged(size_t diff);
};
