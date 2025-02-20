#include "PlayerInfoWidget.h"
#include <QVBoxLayout>

PlayerInfoWidget::PlayerInfoWidget(std::shared_ptr<Game> game, QWidget *parent) : QWidget(parent), game_(game) {
    auto layout = new QVBoxLayout(this);

    player1Label_ = std::make_shared<QLabel>(this);
    player2Label_ = std::make_shared<QLabel>(this);
    currentPlayerLabel_ = std::make_shared<QLabel>(this);

    layout->addWidget(player1Label_.get());
    layout->addWidget(player2Label_.get());
    layout->addWidget(currentPlayerLabel_.get());

    update();
}

void PlayerInfoWidget::update() {
    player1Label_->setText(QString("玩家1: %1 (%2)").arg(game_->getPlayers()[0]->getName().c_str()).arg(game_->getPlayers()[0]->getColor().c_str()));
    player2Label_->setText(QString("玩家2: %1 (%2)").arg(game_->getPlayers()[1]->getName().c_str()).arg(game_->getPlayers()[1]->getColor().c_str()));
    
    auto currentPlayer = game_->getCurrentPlayer();
    if (currentPlayer) {
        if (game_->isGameOver()) {
            currentPlayerLabel_->setText(QString("游戏结束，%1 获胜").arg(currentPlayer->getName().c_str()));
        } else {
            currentPlayerLabel_->setText(QString("当前玩家: %1").arg(currentPlayer->getName().c_str()));
        }
    } else {
        currentPlayerLabel_->setText("游戏未开始");
    }
}
