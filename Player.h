#ifndef CAMPINGSURVIVAL_PLAYER_H
#define CAMPINGSURVIVAL_PLAYER_H

#include <iostream>

/// Move Direction Enum
enum moveDirection {up,down,left,right};

/// Color Structure
struct colorStruct {
    float red;
    float green;
    float blue;

    colorStruct();
    colorStruct(double redIn, double greenIn, double blueIn);
};

/// Position Structure
struct posStruct {
    int xPos;
    int yPos;

    posStruct();
    posStruct(int xIn, int yIn);
};

/// Player Class
class Player {
private:
    posStruct pos;
    colorStruct color;
    double foodLevel;
    double waterLevel;

public:
    // Constructor
    Player();

    /**
     * Requires: Color, Position
     * Modifies: pos, color, foodLevel, waterLevel
     * Effects: Builds the Player object
    */
    Player(colorStruct color, posStruct pos);

    // Methods
    /**
     * Requires: Direction
     * Modifies: pos
     * Effects: Moves the player position in the direction of 'dir'
    */
    void move(moveDirection dir);

    // Getters
    /**
     * Requires: None
     * Modifies: None
     * Effects: Gets the position struct
    */
    posStruct getPos() const;

    /**
     * Requires: None
     * Modifies: None
     * Effects: Gets the color struct
    */
    colorStruct getColor() const;

    /**
     * Requires: None
     * Modifies: None
     * Effects: Gets the food level
    */
    double getFoodLevel() const;

    /**
     * Requires: None
     * Modifies: None
     * Effects: Gets the water level
    */
    double getWaterLevel() const;

    // Setters
    /**
     * Requires: Change amount
     * Modifies: foodLevel
     * Effects: Changes food level by the amount of 'change' positive or negative
    */
    void changeFoodLevel(double change);

    /**
     * Requires: Change amount
     * Modifies: waterLevel
     * Effects: Changes water level by the amount of 'change' positive or negative
    */
    void changeWaterLevel(double change);

    /**
     * Requires: Level
     * Modifies: foodLevel
     * Effects: Sets the food level to the level supplied
    */
    void setFoodLevel(double level);

    /**
     * Requires: Level
     * Modifies: waterLevel
     * Effects: Sets the water level to the level supplied
    */
    void setWaterLevel(double level);

    /**
     * Requires: None
     * Modifies: None
     * Effects: Runs and prints testing for this class
    */
    void testFunctionality();

    /**
     * Requires: None
     * Modifies: None
     * Effects: Prints the data of the Player to text
    */
    friend std::ostream& operator << (std::ostream& outs, const Player &p);

    /**
     * Requires: None
     * Modifies: None
     * Effects: Reads the data of the Player from text
    */
    friend std::istream& operator >> (std::istream& ins, Player &p);

};

#endif