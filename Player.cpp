#include "Player.h"

/// Color Struct
colorStruct::colorStruct(double redIn, double greenIn, double blueIn) {
    red = redIn;
    green = greenIn;
    blue = blueIn;
}

/// Position Struct
posStruct::posStruct(int xIn, int yIn) {
    xPos = xIn;
    yPos = yIn;
}

/// Player Class
// Constructors
Player::Player(colorStruct color, posStruct pos) : color(color), pos(pos) {
    // Set Food and Water
    foodLevel = 100;
    waterLevel = 100;
}

// Methods
void Player::move(moveDirection dir) {
    // Variables
    int moveAmount = 10;

    // Switch to direction
    switch(dir) {
        case up:
            pos.yPos += moveAmount;
            break;

        case down:
            pos.yPos -= moveAmount;
            break;

        case left:
            pos.xPos -= moveAmount;
            break;

        case right:
            pos.xPos += moveAmount;
            break;
    }
}

// Getters
posStruct Player::getPos() const {
    return pos;
}

colorStruct Player::getColor() const {
    return color;
}

double Player::getFoodLevel() const {
    return foodLevel;
}

double Player::getWaterLevel() const {
    return waterLevel;
}

// Setters
void Player::changeFoodLevel(double change) {
    foodLevel += change;
}

void Player::changeWaterLevel(double change) {
    waterLevel += change;
}

void Player::setFoodLevel(double level) {
    foodLevel = level;
}

void Player::setWaterLevel(double level) {
    waterLevel = level;
}
