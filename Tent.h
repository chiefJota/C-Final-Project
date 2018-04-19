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
    /**
     * Requires:
     * Modifies:
     * Effects:sets the color and pos structs as temporary values for testing
    */
    Tent();

    /**
     * Requires:input from mouse on tent object
     * Modifies:
     * Effects:triggers moves to next day function
    */
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
     * this method will not be defined until graphics portion and we decide how to store and display
     * the items graphically
    */
    //double getItems(std::vector<std::unique_ptr<Item>> &items);

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