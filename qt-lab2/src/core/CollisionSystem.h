#pragma once
#include <QVector>
#include "Ball.h"
#include "BallList.h"
#include "Path.h"

class CollisionSystem {
public:
    CollisionSystem();
    
    bool checkPathCollisions(const Ball& shootingBall, BallList& pathBalls, const Path& path);// DONE: modify BallList
    
    struct CollisionResult {
        bool hasCollision;
        int collisionIndex;
    };
    
private:
    CollisionResult findCollision(const Ball& ball, const BallList& ballList) const;// DONE: modify BallList
    void handleCollision(Ball ball, BallList& balls, const Path& path, const int& collisionIndex);// DONE: modify BallList
};
