#include "QStartupMenuWindow.h"

QStartupMenuWindow::QStartupMenuWindow(QMainWindow *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Chess Game");

    startButton = new QPushButton("Start");
    difficultyButton = new QPushButton("Difficulty");
    difficultyDisplayer = new QLCDNumber();
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(startButton);
    layout->addWidget(difficultyButton);

    setLayout(layout);
    connect(difficultyButton, &QPushButton::clicked, &QStartupMenuWindow::changeDifficulty);
    connect(this, &QStartupMenuWindow::difficultyChanged, difficultyDisplayer, qOverload<int>(&QLCDNumber::display));
    
}

QStartupMenuWindow::~QStartupMenuWindow()
{}

void QStartupMenuWindow::changeDifficulty() {
    difficulty++;
    if (difficulty >= 6) {
        difficulty = 0;
    }
    emit difficultyChanged(difficulty);
    return;
}

