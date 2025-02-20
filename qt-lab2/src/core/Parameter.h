#pragma once
#include <QColor>

static constexpr float EPS = 1e-6; // 浮点数精度
static constexpr float BALL_RADIUS = 15.0f; // 球的半径
static constexpr float COLLISION_THRESHOLD = 1.0f; // 碰撞检测阈值
static constexpr float BALL_SPEED = 30.0f;  // 轨道上球的移动速度
static constexpr float SHOOTING_BALL_SPEED = BALL_SPEED * 20;  // 正在飞行的球的飞行速度
static constexpr float SCREEN_MIN_X = 0; // 屏幕最小x坐标
static constexpr float SCREEN_MIN_Y = 0; // 屏幕最小y坐标
static constexpr float SCREEN_MAX_X = 600; // 屏幕最大x坐标
static constexpr float SCREEN_MAX_Y = 600; // 屏幕最大y坐标
static constexpr int MIN_MATCH_COUNT = 3; // 最小匹配消除的数目
static const QVector<QColor> COLORS = {
    QColor(255, 182, 193),  // 粉色马卡龙
    QColor(173, 216, 230),  // 淡蓝马卡龙
    QColor(144, 238, 144),  // 薄荷绿马卡龙
    QColor(221, 130, 241),  // 淡紫马卡龙
    QColor(255, 228, 181)   // 奶油黄马卡龙
};