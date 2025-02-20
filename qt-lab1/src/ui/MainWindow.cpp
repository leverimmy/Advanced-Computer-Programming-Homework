#include "MainWindow.h"
#include "BoardWidget.h"
#include "PlayerInfoWidget.h"
#include "OperationWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    game_ = std::make_shared<Game>();
    setupUi();
    connectSignals();
}

std::shared_ptr<Game> MainWindow::getGame() const {
    return game_;
}

std::shared_ptr<OperationWidget> MainWindow::getOperationWidget() const {
    return operationWidget_;
}

void MainWindow::setupUi() {
    auto centralWidget = new QWidget(this);
    auto mainLayout = new QHBoxLayout(centralWidget);

    boardWidget_ = std::make_shared<BoardWidget>(game_, this);
    playerInfoWidget_ = std::make_shared<PlayerInfoWidget>(game_, this);
    operationWidget_ = std::make_shared<OperationWidget>(this);

    mainLayout->addWidget(boardWidget_.get());

    auto sideLayout = new QVBoxLayout();
    sideLayout->addWidget(playerInfoWidget_.get());
    sideLayout->addWidget(operationWidget_.get());

    mainLayout->addLayout(sideLayout);

    setCentralWidget(centralWidget);
}

void MainWindow::connectSignals() {
    connect(operationWidget_.get(), &OperationWidget::startGameRequested, this, &MainWindow::onGameStart);
    // DONE: 连接悔棋请求信号和悔棋槽函数
    connect(operationWidget_.get(), &OperationWidget::undoRequested, this, &MainWindow::onUndoRequested);
    connect(boardWidget_.get(), &BoardWidget::moveMade, this, &MainWindow::onMoveMade);
}

void MainWindow::onGameStart() {
    game_->start();
    boardWidget_->update();
    playerInfoWidget_->update();
}

void MainWindow::onGameEnd() {
    std::string str = game_->getCurrentPlayer()->getName() + " 获胜！";
    QMessageBox::information(this, "Game Over", str.c_str());
}

void MainWindow::onMoveMade(int row, int col) {
    if (game_->makeMove(row, col)) {
        boardWidget_->update();
        playerInfoWidget_->update();
        if (game_->isGameOver()) {
            onGameEnd();
        }
    }
}

void MainWindow::onUndoRequested() {
    // 实现悔棋功能并更新界面显示
    if (game_->undoMove()) {
        boardWidget_->update();
        playerInfoWidget_->update();
    }
}
