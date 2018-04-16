#include "Player.h"

/// Color Struct
colorStruct::colorStruct() {
    red = 0;
    green = 0;
    blue = 0;
}

colorStruct::colorStruct(double redIn, double greenIn, double blueIn) {
    red = redIn;
    green = greenIn;
    blue = blueIn;
}

/// Position Struct
posStruct::posStruct() {
    xPos = 0;
    yPos = 0;
}

posStruct::posStruct(int xIn, int yIn) {
    xPos = xIn;
    yPos = yIn;
}

/// Player Class
// Constructors
Player::Player() {
    color = colorStruct();
    pos = posStruct();
    foodLevel = 0;
    waterLevel = 0;
}

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

// Text I/O Streams
std::ostream &operator << (std::ostream &outs, const Player &p) {
    // Write variables
    outs << "Player: "
         << p.foodLevel << " "
         << p.waterLevel << " "
         << p.pos.xPos << " "
         << p.pos.yPos << " "
         << p.color.red << " "
         << p.color.green << " "
         << p.color.blue;

    // Return the out stream
    return outs;
}

std::istream &operator >> (std::istream &ins, Player &p) {
    // Remove name from text
    std::string name;
    ins >> name;

    // Assign easy variables
    ins >> p.foodLevel;
    ins >> p.waterLevel;

    // Build position struct
    int x;
    int y;
    ins >> x;
    ins >> y;

    // Assign position struct
    p.pos = posStruct(x,y);

    // Build color struct
    double r;
    double g;
    double b;
    ins >> r;
    ins >> g;
    ins >> b;

    // Assign position struct
    p.color = colorStruct(r,g,b);

    // Return the in stream
    return ins;
}