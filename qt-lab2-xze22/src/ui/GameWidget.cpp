#include "GameWidget.h"

#include "Parameter.h"
#include <QPainter>
#include <QDebug>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
    , game(new Game(this))
    , gameTimer(new QTimer(this))
{
    setMinimumSize(SCREEN_MAX_X, SCREEN_MAX_Y);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);  // 启用鼠标追踪
    
    // 初始化游戏定时器
    gameTimer->setInterval(1000 / FRAME_RATE);
    connect(gameTimer, &QTimer::timeout, this, &GameWidget::updateGame);
    
    // 连接游戏信号
    connect(game, &Game::scoreChanged, this, &GameWidget::handleScoreChanged);
    connect(game, &Game::gameOver, this, &GameWidget::handleGameOver);
    
    // 初始化游戏
    game->initialize();
    gameTimer->start();
}

GameWidget::~GameWidget() {
    gameTimer->stop();
}

void GameWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 绘制背景
    painter.fillRect(rect(), Qt::white);
    
    // 绘制游戏元素
    drawPath(painter);
    drawBalls(painter);
    drawShooter(painter);
}

void GameWidget::drawPath(QPainter &painter) {
    const Path& path = game->getPath();
    const QVector<QPointF>& points = path.getPoints();
    
    if (points.size() < 2) return;
    
    // 绘制路径
    QPen pen(Qt::black, 2);
    painter.setPen(pen);
    
    for (int i = 0; i < points.size() - 1; ++i) {
        painter.drawLine(points[i], points[i + 1]);
    }
}

void GameWidget::drawBalls(QPainter &painter) {
    // DONE: draw BallList
    // 绘制路径上的球
    const BallList& ballList = game->getBallList();
    BallList::BallNode* current = ballList.head;
    while (current != nullptr) {
        QPointF pos = current->ball.getPosition();
        float radius = current->ball.getRadius();
        
        painter.setBrush(current->ball.getColor());
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(pos, radius, radius);
        
        current = current->next;
    }
    
    // 绘制正在飞行的球
    const QVector<Ball>& shootingBalls = game->getShootingBalls();
    for (const Ball& ball : shootingBalls) {
        QPointF pos = ball.getPosition();
        float radius = ball.getRadius();
        
        painter.setBrush(ball.getColor());
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(pos, radius, radius);
    }
}

void GameWidget::drawShooter(QPainter &painter) {
    const Shooter& shooter = game->getShooter();
    QPointF pos = shooter.getPosition();
    float angle = shooter.getAngle();
    
    // 绘制发射器底座
    painter.setBrush(Qt::darkGray);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(pos, 20, 20);
    
    // 绘制发射方向
    painter.setPen(QPen(Qt::black, 2));
    QPointF endPoint = pos + QPointF(cos(angle), sin(angle)) * 30;
    painter.drawLine(pos, endPoint);
    
    // 绘制待发射的球
    if (shooter.isReady()) {
        const Ball& nextBall = shooter.getNextBall();
        painter.setBrush(nextBall.getColor());
        painter.setPen(Qt::NoPen);
        painter.drawEllipse(pos, nextBall.getRadius(), nextBall.getRadius());
    }
}

void GameWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        game->handleClick(event->pos());
        update();
    }
}

void GameWidget::mouseMoveEvent(QMouseEvent *event) {
    lastMousePos = event->pos();
    updateShooterAngle(lastMousePos);
    update();
}

void GameWidget::updateShooterAngle(const QPointF& mousePos) {
    QPointF shooterPos = game->getShooter().getPosition();
    QPointF direction = mousePos - shooterPos;
    float angle = std::atan2(direction.y(), direction.x());
    
    // 获取非const的Shooter引用
    Shooter& shooter = const_cast<Shooter&>(game->getShooter());
    shooter.setAngle(angle);
}

void GameWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    update();
}

void GameWidget::updateGame() {
    game->update(DELTA_TIME);
    update();
}

void GameWidget::handleScoreChanged(int newScore) {
    // 可以在这里添加分数变化的视觉效果
    update();
}

void GameWidget::handleGameOver() {
    gameTimer->stop();
    // 可以在这里添加游戏结束的视觉效果
    update();
}
