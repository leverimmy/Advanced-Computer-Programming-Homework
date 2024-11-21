#pragma once

#include <memory>
#include <vector>
#include "Board.h"
#include "Player.h"

class Game {
public:
    Game();
    ~Game() = default;

    void start();
    void end();
    bool makeMove(int row, int col);
    bool undoMove();
    void switchPlayer();

    const std::shared_ptr<Board> getBoard() const;
    const std::vector<std::shared_ptr<Player>> getPlayers() const;
    const std::shared_ptr<Player> getCurrentPlayer() const;
    bool isGameOver() const;

protected:
    std::shared_ptr<Board> board_;
    std::vector<std::shared_ptr<Player>> players_;
    std::shared_ptr<Player> currentPlayer_;
    bool gameOver_;
};
