#include "CollisionSystem.h"

#include "Parameter.h"
#include "Game.h"
#include <algorithm>

CollisionSystem::CollisionSystem() {
}

// DONE: modify BallList
bool CollisionSystem::checkPathCollisions(const Ball& shootingBall, BallList& pathBalls, const Path& path) {
    CollisionResult result = findCollision(shootingBall, pathBalls);
    
    if (result.hasCollision) {
        handleCollision(shootingBall, pathBalls, path, result.collisionIndex);
    }

    return result.hasCollision;
}

// DONE: modify BallList
CollisionSystem::CollisionResult CollisionSystem::findCollision(
    const Ball& ball, const BallList& ballList) const {
    CollisionResult result = {false, -1};

    auto current = ballList.head;
    int pos = 0;
    while (current != nullptr) {
        auto currentBall = current->ball;
        float distance = ball.distanceTo(currentBall);
        if (distance < ball.getRadius() + currentBall.getRadius() + COLLISION_THRESHOLD) {
            result.hasCollision = true;
            result.collisionIndex = pos;
            break;
        }
        current = current->next;
        pos++;
    }
    return result;
}

// DONE: modify BallList
void CollisionSystem::handleCollision(Ball ball, BallList& ballList, const Path& path, const int& collisionIndex) {
    // 获取碰撞点前后的球
    int prevIndex = (collisionIndex - 1 >= 0) ? collisionIndex - 1 : collisionIndex;
    int nextIndex = (collisionIndex + 1 < ballList.size()) ? collisionIndex + 1 : collisionIndex;

    const Ball& prevBall = ballList[prevIndex];
    const Ball& nextBall = ballList[nextIndex];

    float prevBallDistance = ball.distanceTo(prevBall);
    float nextBallDistance = ball.distanceTo(nextBall);
    
    // 计算插入位置
    int insertIndex = (prevBallDistance < nextBallDistance) ? collisionIndex : collisionIndex + 1;
    if (insertIndex < ballList.size()) {
        ball.setPosition(ballList[insertIndex].getPosition());
    }
    else {
        float currentDistance = path.getDistanceAtPoint(ballList[collisionIndex].getPosition());
        float newDistance = currentDistance + BALL_RADIUS * 2;
        QPointF newPos = path.getPointAtDistance(newDistance);
        ball.setPosition(newPos);
    }
    for (int i = insertIndex; i < ballList.size(); ++i) {
        float currentDistance = path.getDistanceAtPoint(ballList[i].getPosition());
        float newDistance = currentDistance + BALL_RADIUS * 2;
        QPointF newPos = path.getPointAtDistance(newDistance);
        ballList[i].setPosition(newPos);
        if (i < ballList.size() - 1) {
            float distance = ballList[i].distanceTo(ballList[i+1]);
            if (distance > BALL_RADIUS * 2 + EPS) break;
        }
    }

    // 插入球
    ball.setVelocity(QPointF(0, 0));
    ballList.insert(insertIndex, ball);
}
