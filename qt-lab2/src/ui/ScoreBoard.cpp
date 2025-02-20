#include "ScoreBoard.h"
#include <QFont>

ScoreBoard::ScoreBoard(QWidget *parent)
    : QWidget(parent)
    , scoreDisplay(new QLCDNumber(this))
    , gameOverLabel(new QLabel("Game Over!", this))
    , layout(new QVBoxLayout(this))
{
    setupUI();
    reset();
}

void ScoreBoard::setupUI() {
    // 设置分数显示
    scoreDisplay->setDigitCount(6);
    scoreDisplay->setSegmentStyle(QLCDNumber::Filled);
    scoreDisplay->setMinimumHeight(50);
    
    // 设置游戏结束标签
    QFont gameOverFont("Arial", 24, QFont::Bold);
    gameOverLabel->setFont(gameOverFont);
    gameOverLabel->setAlignment(Qt::AlignCenter);
    gameOverLabel->hide();
    
    // 设置布局
    layout->addWidget(scoreDisplay);
    layout->addWidget(gameOverLabel);
    layout->setAlignment(Qt::AlignTop);
    
    // 设置样式
    setStyleSheet(R"(
        QLCDNumber {
            background-color: black;
            color: green;
        }
        QLabel {
            color: red;
        }
    )");
    
    setMinimumWidth(200);
}

void ScoreBoard::reset() {
    scoreDisplay->display(0);
    gameOverLabel->hide();
}

void ScoreBoard::updateScore(int score) {
    scoreDisplay->display(score);
}

void ScoreBoard::showGameOver() {
    gameOverLabel->show();
}