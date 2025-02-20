#pragma once

#include <memory>
#include <QMainWindow>
#include "../core/Game.h"

class BoardWidget;
class PlayerInfoWidget;
class OperationWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    std::shared_ptr<Game> getGame() const;
    std::shared_ptr<OperationWidget> getOperationWidget() const;

private:
    std::shared_ptr<Game> game_;
    std::shared_ptr<BoardWidget> boardWidget_;
    std::shared_ptr<PlayerInfoWidget> playerInfoWidget_;
    std::shared_ptr<OperationWidget> operationWidget_;

    void setupUi();
    void connectSignals();

private slots:
    void onGameStart();
    void onGameEnd();
    void onMoveMade(int row, int col);
    void onUndoRequested();
};
