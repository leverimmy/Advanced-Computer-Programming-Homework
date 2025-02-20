#include "BoardWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

BoardWidget::BoardWidget(std::shared_ptr<Game> game, QWidget *parent) : QWidget(parent), game_(game) {
    cellSize_ = 40;
    setFixedSize(cellSize_ * game_->getBoard()->getCols(), cellSize_ * game_->getBoard()->getRows());
}

void BoardWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 绘制棋盘格子
    for (int i = 0; i < game_->getBoard()->getRows() - 1; ++i) {
        for (int j = 0; j < game_->getBoard()->getCols() - 1; ++j) {
            QRect rect(j * cellSize_ + cellSize_ / 2, i * cellSize_ + cellSize_ / 2, cellSize_, cellSize_);
            painter.drawRect(rect);
        }
    }

    // 绘制棋子
    for (int i = 0; i < game_->getBoard()->getRows(); ++i) {
        for (int j = 0; j < game_->getBoard()->getCols(); ++j) {
            auto piece = game_->getBoard()->getPiece(i, j);
            if (piece) {
                QPoint center = boardToPixel(i, j);
                if (piece->getColor() == "Black") {
                    painter.setBrush(Qt::black);
                } else {
                    painter.setBrush(Qt::white);
                }
                painter.drawEllipse(center, cellSize_ / 2 - 2, cellSize_ / 2 - 2);
            }
        }
    }
}

void BoardWidget::mousePressEvent(QMouseEvent *event) {
    QPoint boardPos = pixelToBoard(event->pos());
    emit moveMade(boardPos.y(), boardPos.x());
}

QPoint BoardWidget::boardToPixel(int row, int col) const {
    return QPoint(col * cellSize_ + cellSize_ / 2, row * cellSize_ + cellSize_ / 2);
}

QPoint BoardWidget::pixelToBoard(const QPoint& pixel) const {
    return QPoint(pixel.x() / cellSize_, pixel.y() / cellSize_);
}
