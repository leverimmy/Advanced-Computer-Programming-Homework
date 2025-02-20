#include "Player.h"

Player::Player(const std::string& name, const std::string& color) : name_(name), color_(color) {}

void Player::setName(const std::string& name) {
    name_ = name;
}

void Player::setColor(const std::string& color) {
    color_ = color;
}

std::string Player::getName() const {
    return name_;
}

std::string Player::getColor() const {
    return color_;
}
