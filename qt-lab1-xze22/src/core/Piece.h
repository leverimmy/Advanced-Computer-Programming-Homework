#pragma once

#include <string>

class Piece {
public:
    Piece(const std::string& color);
    ~Piece() = default;

    void setColor(const std::string& color);
    
    std::string getColor() const;

protected:
    std::string color_;
};
