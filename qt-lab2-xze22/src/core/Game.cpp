#include "Game.h"
#include <QDebug>
#include "Parameter.h"

Game::Game(QObject *parent)
    : QObject(parent)
    , shooter(QPointF(300, 300))  // 发射器位置调整到中间
    , score(0)
    , gameRunning(false)
{
}

void Game::initialize() {
    ballList.clear();
    shootingBalls.clear();
    score = 0;
    gameRunning = true;

    float ballDiameter = BALL_RADIUS * 2;
    float cornerOffset = ballDiameter * 1.5f;

    path.clear();

    // 起点（左上角）
    path.addPoint(QPointF(50, 50));

    // 第一个转角（右上角）
    path.addPoint(QPointF(550 - cornerOffset, 50));
    path.addPoint(QPointF(550, 50 + cornerOffset));

    // 第二个转角（右下角，180度）
    path.addPoint(QPointF(550, 550 - cornerOffset));
    path.addPoint(QPointF(550 - cornerOffset * 1, 550));
    path.addPoint(QPointF(550 - cornerOffset * 2, 550));
    path.addPoint(QPointF(550 - cornerOffset * 3, 550 - cornerOffset));

    // 第三个转角（右上角靠里）
    path.addPoint(QPointF(550 - cornerOffset * 3, 50 + cornerOffset * 3));
    path.addPoint(QPointF(550 - cornerOffset * 4, 50 + cornerOffset * 2));

    // 第四个转角（左上角靠里）
    path.addPoint(QPointF(50 + cornerOffset, 50 + cornerOffset * 2));
    path.addPoint(QPointF(50, 50 + cornerOffset * 3));

    // 第五个转角（左下角靠里）
    path.addPoint(QPointF(50, 550 - cornerOffset));
    path.addPoint(QPointF(50 + cornerOffset, 550));

    // 终点（画面底部）
    path.addPoint(QPointF(300, 550));

    createInitialBalls();
    shooter.setNextBall(Ball(shooter.getPosition(), generateRandomColor()));
}

void Game::update(float deltaTime) {
    if (!gameRunning) return;

    // 更新发射的球
    updateShootingBalls(deltaTime);

    float pathLength = path.getTotalLength();

    // DONE: modify BallList
    // 更新路径上的球，从前向后更新
    BallList::BallNode* current = ballList.head;
    while (current != nullptr) {
        float currentDistance = path.getDistanceAtPoint(current->ball.getPosition());
        float newDistance = currentDistance + BALL_SPEED * deltaTime;
        QPointF newPos = path.getPointAtDistance(newDistance);
        current->ball.setPosition(newPos);
        if (current->next != nullptr && current->ball.distanceTo(current->next->ball) > BALL_RADIUS * 2 + EPS)
            break;
        current = current->next;
    }

    // 检查游戏是否结束
    checkGameOver();
}

void Game::handleClick(const QPointF& point) {
    if (!gameRunning || !shooter.isReady()) return;

    // 计算发射角度
    QPointF shooterPos = shooter.getPosition();
    QPointF direction = point - shooterPos;
    float angle = std::atan2(direction.y(), direction.x());

    // 设置发射角度并发射
    shooter.setAngle(angle);
    Ball shotBall = shooter.shoot();
    shootingBalls.append(shotBall);

    // 准备下一个球
    shooter.setNextBall(Ball(shooter.getPosition(), generateRandomColor()));
}

void Game::updateShootingBalls(float deltaTime) {
    for (int i = shootingBalls.size() - 1; i >= 0; --i) {
        Ball& ball = shootingBalls[i];
        ball.update(deltaTime);

        // 检查球是否飞出屏幕范围
        QPointF pos = ball.getPosition();
        float radius = ball.getRadius();

        if (pos.x() + radius < SCREEN_MIN_X ||
            pos.x() - radius > SCREEN_MAX_X ||
            pos.y() + radius < SCREEN_MIN_Y ||
            pos.y() - radius > SCREEN_MAX_Y)
        {
            shootingBalls.removeAt(i);
            continue;
        }

        // DONE: modify BallList
        // 检查碰撞
        bool hasCollision = collisionSystem.checkPathCollisions(ball, ballList, path);
        if (hasCollision) {
            shootingBalls.removeAt(i);
            checkMatches();
        }
    }
    checkGameOver();
}

void Game::checkMatches() {
    while (ballList.size() >= 3) {
        BallList::BallNode* begin = ballList.head;
        BallList::BallNode* current = begin;
        int count = 0;
        while (current != nullptr) {
            if (current->ball.getColor() == begin->ball.getColor()) {
                count++;
            } else {
                if (count >= 3) {
                    ballList.erase(begin, current);
                    emit scoreChanged(score += count * 100);
                    break;
                }
                begin = current;
                count = 1;
            }
            current = current->next;
        }
        if (current == nullptr && count >= 3) {
            ballList.erase(begin, current);
            emit scoreChanged(score += count * 100);
        }
        if (count < 3) {
            break;
        }
    }
}

void Game::createInitialBalls() {
    const float ballSpacing = BALL_RADIUS * 2;
    float distance = 0;

    while (distance < path.getTotalLength() / 2) { // 只创建一半的路径长度
        QPointF pos = path.getPointAtDistance(distance);
        QPointF nextPos = path.getPointAtDistance(distance + 0.1f); // 获取稍远一点的位置来计算方向

        // 计算单位方向向量
        QPointF direction = nextPos - pos;
        float length = std::sqrt(QPointF::dotProduct(direction, direction));
        if (length > 0) {
            direction /= length;
        }

        // DONE: modify BallList
        // 创建球并设置飞行速度为0
        Ball ball(pos, generateRandomColor());
        ballList.append(ball);

        distance += ballSpacing;
    }
}

QColor Game::generateRandomColor() const {
    return COLORS[QRandomGenerator::global()->bounded(COLORS.size())];
}

void Game::checkGameOver() {
    // DONE: modify BallList
    if (!ballList.isEmpty()) {
        QPointF ballPos = ballList.last().getPosition();
        QPointF endPoint = path.getPoints().last();

        // 计算两点之间的距离
        QPointF diff = ballPos - endPoint;
        float distance = std::sqrt(QPointF::dotProduct(diff, diff));

        if (distance < BALL_RADIUS) {
            gameRunning = false;
            emit gameOver();
        }
    }
    else {
        score += 200;
        emit scoreChanged(score);
        gameRunning = false;
        emit gameOver();
    }
}
