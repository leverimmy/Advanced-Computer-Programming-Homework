#include "Board.h"
#include "Piece.h"

Board::Board(int rows, int cols) : rows_(rows), cols_(cols) {
    grid_.resize(rows_, std::vector<std::shared_ptr<Piece>>(cols_, nullptr));
}

void Board::clear() {
    for (auto& row : grid_) {
        std::fill(row.begin(), row.end(), nullptr);
    }
    while (!moves_.empty()) {
        moves_.pop();
    }
}

bool Board::setPiece(int row, int col, std::shared_ptr<Piece> piece) {
    if (!isValidPosition(row, col) || grid_[row][col]) {
        return false;
    }
    grid_[row][col] = piece;
    moves_.push(std::make_pair(row, col));
    return true;
}

bool Board::isValidPosition(int row, int col) const {
    return row >= 0 && row < rows_ && col >= 0 && col < cols_;
}

bool Board::isGameOver(int row, int col) const {
    const std::shared_ptr<Piece> currentPiece = getPiece(row, col);
    if (!currentPiece) return false;

    const std::string color = currentPiece->getColor();
    const int directions[4][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}};

    for (const auto& dir : directions) {
        int leftExtend = 0, rightExtend = 0;

        // 向左/左上/上/右上方向延伸
        for (int i = 1; i <= 4; ++i) {
            int newRow = row - i * dir[0];
            int newCol = col - i * dir[1];
            if (!isValidPosition(newRow, newCol) 
                || !getPiece(newRow, newCol) 
                || getPiece(newRow, newCol)->getColor() != color) break;
            ++leftExtend;
        }

        // 向右/右下/下/左下方向延伸
        for (int i = 1; i <= 4; ++i) {
            int newRow = row + i * dir[0];
            int newCol = col + i * dir[1];
            if (!isValidPosition(newRow, newCol) 
                || !getPiece(newRow, newCol) 
                || getPiece(newRow, newCol)->getColor() != color) break;
            ++rightExtend;
        }

        // 检查是否有五子连珠
        if (leftExtend + rightExtend >= 4) {
            return true;
        }
    }
    return false;
}

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

std::shared_ptr<Piece> Board::getPiece(int row, int col) const {
    if (!isValidPosition(row, col)) {
        return nullptr;
    }
    return grid_[row][col];
}
