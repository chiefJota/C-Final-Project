#ifndef CAMPINGSURVIVAL_ITEMS_H
#define CAMPINGSURVIVAL_ITEMS_H

#include <iostream>
#include "Player.h"

class Item {
protected:
    std::string name;
    colorStruct color;
    posStruct pos;
    bool isPoisonous;

public:

    /**
    * Default Constructor
    */
    Item();

    /**
     * Non-Default Constructor
     * Requires: name, color, position
     * Modifies: name, color, posiiton
     * Effects: template for subclasses
     * FoodItem and WaterItem
    */
    Item(std::string &name, colorStruct color, posStruct pos);

    /**
     * getters which are
     * all pure virtual methods
     * to be overriden
     * @return
     */
    virtual std::string getItem() = 0;

    virtual colorStruct getColor() = 0;

    virtual posStruct getPosition() = 0;

    /**
     * setters which are all
     * pure virtual
     * to be overriden
     * @param name
     * @return
     */
    virtual std::string setName(std::string name) = 0;

    virtual colorStruct setColor(colorStruct color) = 0;

    virtual posStruct setPos(posStruct pos) = 0;

    /**
     * isMushroom function
     * is pure virtual and is
     * overriden in foodItem
     * and WaterItem classes
     */
    virtual bool isMushroom() = 0;

};

class FoodItem : public Item {

public:

    /**
    * Default Constructor
    */
    FoodItem();

    /**
    * Non-Default Constructor
    * Requires: name, color, position
    * Modifies: name, color, posiiton
    * Effects: sets name, color, and spawning
     * position of the food item
   */
    FoodItem(std::string &name, colorStruct color, posStruct pos);

    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: gets the position
     * of the food item
     *
     */
    posStruct getPosition() override ;


    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: gets the color
     * of the food item
     */
    colorStruct getColor() override;

    /**
    * Requires: Nothing
    * Modifies: Nothing
    * Effects: gets the name
    * of the food item
    */
    std::string getItem() override ;


    /**
    * Requires: Nothing
    * Modifies: food item name
    * Effects: sets the name
    * of the food item
    */
    std::string setName(std::string n) override;

    /**
    * Requires: colorStruct color
    * Modifies: food item color
    * Effects: sets the Color
    * of the food item
    */
    colorStruct setColor(colorStruct color) override;

    /**
    * Requires: posStruct
    * Modifies: food item position
    * Effects: sets the spawning positon
    * of the food item
    */
    posStruct setPos(posStruct pos) override;

    /**
     * Requires: Nothing
     * Modifies: determines if the
     * food item is poisionous or not (true or false)
     * Effects: the player will be affected
     * by eating a fooditem that is poisonous
     *
     */
    bool isMushroom() override;

    /**
     * Testing function for FoodItem class
     */
    void testFoodItem();

};

class WaterItem : public Item {

public:

    /**
     * Default Constructor
     */
    WaterItem();

    /**
    * Non-Default Constructor
    * Requires: name, color, position
    * Modifies: name, color, posiiton
    * Effects: sets name, color, and spawning
    * position of the Water item
    */
    WaterItem(std::string &name, colorStruct color, posStruct pos);

    /**
    * Requires: Nothing
    * Modifies: Nothing
    * Effects: gets the name
    * of the water item
    */
    std::string getItem() override;

    /**
     * Requires: Nothing
     * Modifies: Nothing
     * Effects: gets the position
     * of the water item
     *
     */
    posStruct getPosition() override;


    /**
    * Requires: Nothing
    * Modifies: Nothing
    * Effects: gets the color
    * of the water item
    */
    colorStruct getColor() override;

    /**
    * Requires: Nothing
    * Modifies: food item name
    * Effects: sets the name
    * of the water item
    */
    std::string setName(std::string n) override;


    /**
    * Requires: colorStruct color
    * Modifies: food item color
    * Effects: sets the Color
    * of the water item
    */
    colorStruct setColor(colorStruct color) override;

    /**
    * Requires: posStruct pos
    * Modifies: food item position
    * Effects: sets the spawning positon
    * of the water item
    */
    posStruct setPos(posStruct pos) override;

    /**
    * Requires: Nothing
    * Modifies: determines if the
    * food item is poisionous or not (true or false)
    * Effects: the player will be affected
    * by eating a fooditem that is poisonous
    *
    */
    bool isMushroom() override;


    /**
     * Testing function for WaterItem
     *
     */
    void testWaterItem();


};




#endif