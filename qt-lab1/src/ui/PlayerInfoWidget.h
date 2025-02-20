#pragma once

#include <memory>
#include <QLabel>
#include <QWidget>
#include "../core/Game.h"

class PlayerInfoWidget : public QWidget {
    Q_OBJECT

public:
    PlayerInfoWidget(std::shared_ptr<Game> game, QWidget *parent = nullptr);

public slots:
    void update();

private:
    std::shared_ptr<Game> game_;
    std::shared_ptr<QLabel> player1Label_;
    std::shared_ptr<QLabel> player2Label_;
    std::shared_ptr<QLabel> currentPlayerLabel_;
};
