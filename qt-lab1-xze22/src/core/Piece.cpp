#include "Piece.h"

Piece::Piece(const std::string& color) : color_(color) {}

void Piece::setColor(const std::string& color) {
    color_ = color;
}

std::string Piece::getColor() const {
    return color_;
}
