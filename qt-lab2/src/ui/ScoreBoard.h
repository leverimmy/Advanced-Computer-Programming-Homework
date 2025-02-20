#pragma once
#include <QWidget>
#include <QLCDNumber>
#include <QLabel>
#include <QVBoxLayout>

class ScoreBoard : public QWidget {
    Q_OBJECT
public:
    explicit ScoreBoard(QWidget *parent = nullptr);
    void reset();

public slots:
    void updateScore(int score);
    void showGameOver();

private:
    QLCDNumber *scoreDisplay;
    QLabel *gameOverLabel;
    QVBoxLayout *layout;
    
    void setupUI();
};
