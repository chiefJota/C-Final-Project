#ifndef CAMPINGSURVIVAL_PLAYER_H
#define CAMPINGSURVIVAL_PLAYER_H

/// Move Direction Enum
enum moveDirection {up,down,left,right};

/// Color Structure
struct colorStruct {
    double red;
    double green;
    double blue;

    colorStruct(double redIn, double greenIn, double blueIn);
};

/// Position Structure
struct posStruct {
    int xPos;
    int yPos;

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

};

#endif