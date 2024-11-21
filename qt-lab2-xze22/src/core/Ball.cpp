#include "Ball.h"

#include "Parameter.h"
#include <cmath>

Ball::Ball(const QPointF& pos, const QColor& col) 
    : position(pos)
    , velocity(QPointF(0, 0))
    , color(col)
    , radius(BALL_RADIUS)
{
}

void Ball::setPosition(const QPointF& pos) {
    position = pos;
}

void Ball::setVelocity(const QPointF& vel) {
    velocity = vel;
}

void Ball::setColor(const QColor& col) {
    color = col;
}

QPointF Ball::getPosition() const {
    return position;
}

QPointF Ball::getVelocity() const {
    return velocity;
}

QColor Ball::getColor() const {
    return color;
}

float Ball::getRadius() const {
    return radius;
}

void Ball::update(float deltaTime) {
    // 更新球的位置
    position += velocity * deltaTime;
}

bool Ball::collidesWith(const Ball& other) const {
    // 检查两个球是否碰撞
    float minDistance = radius + other.radius;
    return distanceTo(other) <= minDistance;
}

float Ball::distanceTo(const Ball& other) const {
    // 计算两个球心之间的距离
    QPointF diff = position - other.position;
    return std::sqrt(QPointF::dotProduct(diff, diff));
}