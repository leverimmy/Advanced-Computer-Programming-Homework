#pragma once
#include "Ball.h"
#include <QPointF>

class Shooter {
public:
    Shooter(const QPointF& position);
    
    void setPosition(const QPointF& pos);
    void setAngle(float angle);
    void setNextBall(const Ball& ball);
    void setShootingSpeed(float speed);
    
    Ball shoot();
    void update(float deltaTime);
    QPointF getPosition() const;
    float getAngle() const;
    Ball getNextBall() const;
    bool isReady() const;
    
private:
    QPointF position;
    float angle;         // 发射角度（弧度）
    Ball nextBall;       // 下一个要发射的球
    bool ready;          // 是否准备好发射
    float shootingSpeed; // 发射速度
};