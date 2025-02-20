#pragma once

#include <string>

class Player {
public:
    Player(const std::string& name, const std::string& color);
    ~Player() = default;

    void setName(const std::string& name);
    void setColor(const std::string& color);

    std::string getName() const;
    std::string getColor() const;

protected:
    std::string name_;
    std::string color_;
};
