#pragma once

#include <memory>
#include <QWidget>
#include "../core/Game.h"

class BoardWidget : public QWidget {
    Q_OBJECT

public:
    BoardWidget(std::shared_ptr<Game> game, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void moveMade(int row, int col);

private:
    std::shared_ptr<Game> game_;
    int cellSize_;

    QPoint boardToPixel(int row, int col) const;
    QPoint pixelToBoard(const QPoint& pixel) const;
};
