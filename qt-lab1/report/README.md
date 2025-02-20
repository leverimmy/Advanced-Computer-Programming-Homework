# Lab1

## 项目实现说明

### `Board.h` 和 `Board.cpp`

#### `Board.h`

我在 `Board` 类中添加了成员变量 `moves_`。它是一个栈，其中每个元素都是一个 `std::pair<int, int>`，用来表示每一步棋的落子位置。

```cpp
class Board {
    // ...
    std::stack<std::pair<int, int>> moves_;
};
```

#### `Board.cpp`

我修改了 `clear()` 函数。这是因为在每次初始化棋盘时，都应清空 `moves_`。

```cpp
void Board::clear() {
	// ...
    while (!moves_.empty()) {
        moves_.pop();
    }
}
```

我补全了 `setPiece()` 函数。在落子时，应当同时更新 `moves_`，将最新的一次落子位置压入栈中。

```cpp
bool Board::setPiece(int row, int col, std::shared_ptr<Piece> piece) {
    // ...
    moves_.push(std::make_pair(row, col));
	// ...
}
```

我补全了 `undoLastMove()` 函数。当 `moves_` 非空时，可以弹出栈顶的落子位置以实现“悔棋”的操作。同时，需要修改 `grid_[][]`，将该棋子从棋盘上拿走。

```cpp
bool Board::undoLastMove() {
    // DONE: 使用栈实现悔棋功能，并返回是否成功
    if (moves_.empty()) {
        return false;
    }
    std::pair<int, int> lastMove = moves_.top();
    moves_.pop();
    // 把棋子拿走
    grid_[lastMove.first][lastMove.second] = nullptr;
    return true;
}
```

### `OperationWidget.cpp` 和 `MainWindow.cpp`

#### `OperationWidget.cpp`

我连接了悔棋按钮（`undoButton`）的点击信号（`QPushButton::clicked`）和悔棋请求信号（`OperationWidget::undoRequested`）。

```cpp
connect(undoButton_.get(), &QPushButton::clicked, this, &OperationWidget::undoRequested);
```

#### `MainWindow.cpp`

我连接了悔棋请求信号（`OperationWidget::undoRequested`）和悔棋槽函数（`MainWindow::onUndoRequested`）。

```cpp
connect(operationWidget_.get(), &OperationWidget::undoRequested, this, &MainWindow::onUndoRequested);
```

## AI 使用情况报告

我在完成此次作业的过程中**未使用 AI**。