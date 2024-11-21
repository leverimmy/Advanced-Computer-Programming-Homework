#include <QtTest>
#include "../src/core/BallList.h"
#include "../src/core/Game.h"
#include "../src/core/Parameter.h"

class GameTest : public QObject {
    Q_OBJECT
    
private slots:
    void testBallCollisionAndMatch();
    
private:
    void verifyBallSequence(const BallList& ballList, const QVector<QColor>& expectedColors);
    void simulateShot(Game& game, QPointF target);
};

void GameTest::testBallCollisionAndMatch() {
    Game game;
    // 设置游戏初始状态
    game.initialize();
    game.getBallList().clear();
    
    // 创建一个固定的初始球序列
    BallList ballList;
    QVector<QColor> colors = {
        COLORS[1],
        COLORS[0], 
        COLORS[0], 
        COLORS[1], 
        COLORS[1], 
        COLORS[2], 
        COLORS[3], 
        COLORS[3],
        COLORS[2], 
        COLORS[2], 
        COLORS[1], 
        COLORS[1], 
        COLORS[0],
        COLORS[1] 
    };
    float distance = 0;
    for (const QColor& color : colors) {
        Ball ball(QPointF(50 + distance, 50), color);
        game.getBallList().append(ball);
        distance += BALL_RADIUS * 2;
    }
    
    // 验证初始序列
    verifyBallSequence(game.getBallList(), colors);
    
    // 发射一个球，瞄准第7个球和第8个球之间
    Shooter& shooter = const_cast<Shooter&>(game.getShooter());
    shooter.setNextBall(Ball(shooter.getPosition(), COLORS[3]));
    simulateShot(game, QPointF(50 + BALL_RADIUS * 11, 50));
    
    // 等待球碰撞和消除
    for (int i = 0; i < 180; ++i) {
        game.update(0.016f); // 60fps
    }
    
    // 验证消除后的序列
    QVector<QColor> expectedColors = {COLORS[1], COLORS[1]};
    verifyBallSequence(game.getBallList(), expectedColors);

    // 第二次发射一个球
    shooter.setNextBall(Ball(shooter.getPosition(), COLORS[1]));
    simulateShot(game, QPointF(50 + BALL_RADIUS * 6, 50));
    
    // 等待球碰撞和消除
    for (int i = 0; i < 180; ++i) {
        game.update(0.016f); // 60fps
    }

    // 验证消除后的序列
    expectedColors.clear();
    verifyBallSequence(game.getBallList(), expectedColors);
}

void GameTest::verifyBallSequence(const BallList& ballList, const QVector<QColor>& expectedColors) {
    BallList::BallNode* currentNode = ballList.head;
    qDebug() << "CURRENT";
    BallList::BallNode* cur = ballList.head;
    while (cur != nullptr) {
        qDebug() << cur->ball.getColor();
        cur = cur->next;
    }
    qDebug() << "EXPECTED";
    for (int i = 0; i < expectedColors.size(); ++i) {
        qDebug() << expectedColors[i];
    }
    for (int i = 0; i < expectedColors.size(); ++i) {
        if (currentNode == nullptr) {
            QFAIL("Ball sequence is shorter than expected");
        }
        QCOMPARE(currentNode->ball.getColor(), expectedColors[i]);
        currentNode = currentNode->next;
    }
    if (currentNode != nullptr) {
        QFAIL("Ball sequence is longer than expected");
    }
}

void GameTest::simulateShot(Game& game, QPointF target) {
    game.handleClick(target);
}

QTEST_MAIN(GameTest)
#include "GameTest.moc"
