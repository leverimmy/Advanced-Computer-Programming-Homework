#include "Shooter.h"

#include "Parameter.h"
#include <cmath>

Shooter::Shooter(const QPointF& pos)
    : position(pos)
    , angle(0.0f)
    , nextBall(pos)
    , ready(true)
    , shootingSpeed(SHOOTING_BALL_SPEED)
{
}

void Shooter::setPosition(const QPointF& pos) {
    position = pos;
    if (ready) {
        nextBall.setPosition(pos);
    }
}

void Shooter::setAngle(float newAngle) {
    angle = newAngle;
}

void Shooter::setNextBall(const Ball& ball) {
    nextBall = ball;
    nextBall.setPosition(position);
    ready = true;
}

void Shooter::setShootingSpeed(float speed) {
    shootingSpeed = speed;
}

Ball Shooter::shoot() {
    if (!ready) {
        return Ball();
    }
    
    // 计算发射速度向量
    float vx = shootingSpeed * std::cos(angle);
    float vy = shootingSpeed * std::sin(angle);
    
    Ball shootingBall = nextBall;
    shootingBall.setVelocity(QPointF(vx, vy));
    
    ready = false;
    return shootingBall;
}

void Shooter::update(float deltaTime) {
    // 可以在这里添加发射器的动画效果
}

QPointF Shooter::getPosition() const {
    return position;
}

float Shooter::getAngle() const {
    return angle;
}

Ball Shooter::getNextBall() const {
    return nextBall;
}

bool Shooter::isReady() const {
    return ready;
}