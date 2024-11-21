#pragma once
#include <QColor>
#include <QPointF>
#include "Parameter.h"

class Ball {
public:
    Ball(const QPointF& pos = QPointF(), const QColor& color = COLORS[0]);
    
    void setPosition(const QPointF& pos);
    void setVelocity(const QPointF& vel);
    void setColor(const QColor& color);
    
    QPointF getPosition() const;
    QPointF getVelocity() const;
    QColor getColor() const;
    float getRadius() const;
    
    void update(float deltaTime);
    bool collidesWith(const Ball& other) const;
    float distanceTo(const Ball& other) const;

private:
    QPointF position;    // 球的位置
    QPointF velocity;    // 球的速度向量
    QColor color;       // 球的颜色
    float radius;       // 球的半径
};