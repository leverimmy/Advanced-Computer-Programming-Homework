#pragma once
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include "../core/Game.h"

class GameWidget : public QWidget {
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget();
    Game* getGame() const { return game; }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void updateGame();
    void handleScoreChanged(int newScore);
    void handleGameOver();

private:
    Game *game;
    QTimer *gameTimer;
    QPointF lastMousePos;
    
    void drawBalls(QPainter &painter);
    void drawPath(QPainter &painter);
    void drawShooter(QPainter &painter);
    void updateShooterAngle(const QPointF& mousePos);
    
    static constexpr int FRAME_RATE = 60;
    static constexpr float DELTA_TIME = 1.0f / FRAME_RATE;
};