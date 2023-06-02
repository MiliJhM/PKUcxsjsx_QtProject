#include "QStartupMenuWindow.h"
#define pass  
QStartupMenuWindow::QStartupMenuWindow(QMainWindow *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Chess Game");

    ui.setupUi(this);
    difficulty = 0;
    connect(ui.DifficultyButton, &QPushButton::clicked, this, &QStartupMenuWindow::changeDifficulty);
    connect(this, &QStartupMenuWindow::difficultyChanged, ui.lcdNumber, qOverload<int>(&QLCDNumber::display));
    connect(ui.LoadButton, &QPushButton::clicked, this, &QStartupMenuWindow::loadGame);
    connect(ui.StartButton, &QPushButton::clicked, this, &QStartupMenuWindow::startNew);
    
}

QStartupMenuWindow::~QStartupMenuWindow()
{
    pass;
}

void QStartupMenuWindow::connectToGameWindow(QGameWindow* gw) {
    connect(gw, &QGameWindow::startupCompleted, this, &QStartupMenuWindow::startupCompleted);
    connect(gw, &QGameWindow::menuReopen, this, &QStartupMenuWindow::reopen);
    connect(this, &QStartupMenuWindow::newStarted, gw, &QGameWindow::newGameInit);
    connect(this, &QStartupMenuWindow::gameLoaded, gw, &QGameWindow::loadGame);
}

void QStartupMenuWindow::changeDifficulty() {
    difficulty++;
    if (difficulty >= 6) {
        difficulty = 0;
    }
    emit difficultyChanged(difficulty);
    qDebug("[INFO]: ChangeDifficulty:%d", difficulty);
    return;
}

void QStartupMenuWindow::startNew() {
    qDebug("[INFO]: NewGameStarted@Difficulty %d", difficulty);
    emit newStarted(difficulty);
    return;
}

void QStartupMenuWindow::loadGame() {
    QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("´æµµ"), "F:", QStringLiteral("´æµµÎÄ¼þ(*.dat)"));
    QFile loadFile(fileName, this);
    if (loadFile.exists()) {
        emit gameLoaded(loadFile);

        qDebug("[INFO]: LoadGameFrom: %s", fileName.toStdString().c_str());
    }
    else
        qDebug("[WARNING]: LoadFailed: loadFileNOTExist");
    return;
}

void QStartupMenuWindow::startupCompleted(QGameWindow& mw) {
    qDebug("[INFO]: StartupCompleted, MenuWindowClosed");
    close();
    mw.show();
    return;
}

void QStartupMenuWindow::reopen(QGameWindow& mw) {
    qDebug("[INFO]: Exit MainWindow, Menu reopen");
    mw.close();
    show();
    return;
}

