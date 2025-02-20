#include "MainWindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDockWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , gameWidget(new GameWidget(this))
    , scoreBoard(new ScoreBoard(this))
{
    setupUI();
    createMenus();
    createDockWidgets();
    
    // 设置窗口标题和大小
    setWindowTitle(tr("Zuma Game"));
    resize(800, 600);
}

void MainWindow::setupUI() {
    // 设置中央部件为游戏窗口
    setCentralWidget(gameWidget);
}

void MainWindow::createMenus() {
    // 创建游戏菜单
    QMenu *gameMenu = menuBar()->addMenu(tr("游戏"));
    
    QAction *newGameAction = new QAction(tr("新游戏"), this);
    newGameAction->setShortcut(QKeySequence::New);
    connect(newGameAction, &QAction::triggered, this, &MainWindow::startNewGame);
    gameMenu->addAction(newGameAction);
    
    gameMenu->addSeparator();
    
    QAction *exitAction = new QAction(tr("退出"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    gameMenu->addAction(exitAction);
    
    // 创建帮助菜单
    QMenu *helpMenu = menuBar()->addMenu(tr("帮助"));
    
    QAction *aboutAction = new QAction(tr("关于"), this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
    helpMenu->addAction(aboutAction);
}

void MainWindow::createDockWidgets() {
    // 创建记分板停靠窗口
    QDockWidget *scoreDock = new QDockWidget(tr("分数"), this);
    scoreDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    scoreDock->setWidget(scoreBoard);
    addDockWidget(Qt::RightDockWidgetArea, scoreDock);
    
    // 连接游戏信号到记分板
    connect(gameWidget->getGame(), &Game::scoreChanged, scoreBoard, &ScoreBoard::updateScore);
    connect(gameWidget->getGame(), &Game::gameOver, scoreBoard, &ScoreBoard::showGameOver);
}

void MainWindow::startNewGame() {
    gameWidget->getGame()->initialize();
    scoreBoard->reset();
}

void MainWindow::showAbout() {
    QMessageBox::about(this, tr("关于 Zuma"),
        tr("Zuma 游戏\n"
           "版本 1.0\n"
           "一个基于Qt的简单Zuma游戏实现"));
}