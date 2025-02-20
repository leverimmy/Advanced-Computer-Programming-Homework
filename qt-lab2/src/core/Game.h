#pragma once
#include <QObject>
#include "Ball.h"
#include "Path.h"
#include "Shooter.h"
#include "CollisionSystem.h"
#include <QRandomGenerator>

class Game : public QObject {
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    
    void initialize();
    void update(float deltaTime);
    void handleClick(const QPointF& point);
    
    // 获取游戏状态的方法，供UI使用
    int getScore() const { return score; }
    const Path& getPath() const { return path; }
    const Shooter& getShooter() const { return shooter; }
    const QVector<Ball>& getShootingBalls() const { return shootingBalls; }
    BallList& getBallList() { return ballList; }
    
signals:
    void scoreChanged(int score);
    void gameOver();

private:
    Path path;
    Shooter shooter;
    BallList ballList;
    QVector<Ball> shootingBalls;  // 正在飞行的球
    CollisionSystem collisionSystem;
    int score;
    bool gameRunning;
    
    void checkMatches();
    void removeMatchedBalls();
    void createInitialBalls();
    QColor generateRandomColor() const;
    void updateShootingBalls(float deltaTime);
    void checkGameOver();
};
