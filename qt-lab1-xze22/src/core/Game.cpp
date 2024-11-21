#include "Game.h"

Game::Game() {
    board_ = std::make_shared<Board>(15, 15);  // 15x15 的标准五子棋棋盘
    players_.push_back(std::make_shared<Player>("Alice", "Black"));
    players_.push_back(std::make_shared<Player>("Bob", "White"));
    currentPlayer_ = nullptr;
    gameOver_ = true;
}

void Game::start() {
    board_->clear();
    currentPlayer_ = players_[0];
    gameOver_ = false;
}

void Game::end() {
    gameOver_ = true;
}

bool Game::makeMove(int row, int col) {
    if (gameOver_ || !board_->isValidPosition(row, col) || board_->getPiece(row, col)) {
        return false;
    }

    auto piece = std::make_shared<Piece>(currentPlayer_->getColor());
    board_->setPiece(row, col, piece);

    if (board_->isGameOver(row, col)) {
        end();
        return true;
    }

    switchPlayer();
    return true;
}

bool Game::undoMove() {
    // 实现悔棋功能并切换玩家
    if (gameOver_) {
        return false;
    }
    if (board_->undoLastMove()) {
        switchPlayer();
        return true;
    }
    return false;
}

void Game::switchPlayer() {
    currentPlayer_ = (currentPlayer_ == players_[0]) ? players_[1] : players_[0];
}

const std::shared_ptr<Board> Game::getBoard() const {
    return board_;
}

const std::vector<std::shared_ptr<Player>> Game::getPlayers() const {
    return players_;
}

const std::shared_ptr<Player> Game::getCurrentPlayer() const {
    return currentPlayer_;
}

bool Game::isGameOver() const {
    return gameOver_;
}
