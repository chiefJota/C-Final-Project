#ifndef CAMPINGSURVIVAL_TENT_H
#define CAMPINGSURVIVAL_TENT_H

#include "player.h"
#include "Items.h"
#include <vector>
#include <ctime>
#include <memory>


class Tent {
protected:
    colorStruct color;
    posStruct pos;
    int curDay = 0;
    double curTime;
    double startTime = 100;
    std::vector<std::unique_ptr<Item>> items;
    int dayOut;


public:
    Tent();

    // Handle mouse button pressed and released events
    void mouse(int button, int state, int x, int y);

    /**
     * Requires:
     * Modifies:
     * Effects:moves to next day
    */
    void goToNextDay();

    /**
    * Requires:
    * Modifies:
    * Effects:gets color
    */
    colorStruct getColor() const;

    /**
     * Requires:
     * Modifies:
     * Effects:gets position
    */
    posStruct getPos() const;

    /**
     * Requires:items are necessary and cannot be added until graphic portion
     * Modifies:
     * Effects:gets items
    */
    double getItems(std::vector<std::unique_ptr<Item>> &items);

    /**
     * Requires:
     * Modifies:
     * Effects:sets up timer for each day
    */
    void setTime(double startTime);

    /**
     * Requires:
     * Modifies:
     * Effects:gets current time
    */
    double getCurrentTime();

    /**
     * Requires:
     * Modifies:
     * Effects:counts down current time according to program iterations
    */
    bool tick();

    /**
     * Requires:
     * Modifies:
     * Effects:gets the day
    */
    int getDay();

    //Tester function
    void testTent();

};

#endif