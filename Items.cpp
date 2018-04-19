//
// Created by Workstation2 on 4/10/2018.
//

#include "Items.h"

#include <regex>

//default constructor
Item::Item() {

}

//non default constructor
Item::Item(std::string &name, colorStruct color, posStruct pos) {
    name = " ";
    this->color = color;
    this->pos = pos;
}


//default constructor for FoodItem
FoodItem::FoodItem(){

}

//non default constructor for FoodItem
FoodItem::FoodItem(std::string &n, colorStruct color, posStruct pos) {
    name = n;
    this->color = color;
    this->pos = pos;
}

/**
 * Getters for FoodItem
 */
std::string FoodItem::getItem() {
    return name;
}

posStruct FoodItem::getPosition() {
    return  pos;
}

colorStruct FoodItem::getColor() {
    return color;
}


/**
 * Setters for FoodItem
 */
std::string FoodItem::setName(std::string food) {
    name = food;
}
colorStruct FoodItem::setColor(colorStruct Color) {
    color = Color;
}

posStruct FoodItem::setPos(posStruct position) {
    pos = position;
}

/**
 * isMushroom method
 */
bool::FoodItem::isMushroom() {

    /*
    * Random 1 to 100
    * if Random <= 25
    *      isPoisonous = true
    * else
    *      isP = false
    */

    srand(time(NULL));

    int MIN_CHANCE = 1;
    int MAX_CHANCE = 100;

    int poisonChance = rand() % MAX_CHANCE + MIN_CHANCE;

    if (poisonChance < 25){
        isPoisonous = true;
    }
    else{
        isPoisonous= false;
    }

    return isPoisonous;
}

//default constructor for WaterItem
WaterItem::WaterItem(){

}

//no default constructor for WaterItem
WaterItem::WaterItem(std::string &n, colorStruct color, posStruct pos) {
    name = n;
    this->color = color;
    this->pos = pos;
}

/**
 * Getters for WaterItem
 */
std::string WaterItem::getItem() {
    return name;
}

posStruct WaterItem::getPosition() {
    return pos;
}

colorStruct WaterItem::getColor() {
    return color;
}

/**
 * Setters for WaterItem
 * @param water
 * @return
 */
std::string WaterItem::setName(std::string water) {
    name = water;
}

posStruct WaterItem::setPos(posStruct position) {
    pos = position;
}

colorStruct WaterItem::setColor(colorStruct Color) {
    color = Color;
}

/**
 * isMushroom method for WaterItem
 * @return
 */
bool ::WaterItem::isMushroom() {

    srand(time(NULL));

    int MIN_CHANCE = 1;
    int MAX_CHANCE = 100;

    int poisonChance = rand() % MAX_CHANCE + MIN_CHANCE;

    if (poisonChance < 25){
        isPoisonous = true;
    }
    else{
        isPoisonous= false;
    }

    return isPoisonous;
}



/**
 * testing function for FoodItem
 */
void FoodItem::testFoodItem(){

    std::cout << "Food Item Before:" << this << std::endl;
    setName("Berries");
    //getters
    std::cout << "Food Item name: " << getItem() << std::endl;
    std::cout << "getPos: (" << getPosition().xPos << "," << getPosition().yPos << ")" << std::endl;
    std::cout << "getColor: RGB(" << getColor().red << "," << getColor().green << "," << getColor().blue << ")" << std::endl;
    std::cout << std::boolalpha << isMushroom() << std::endl;

    name = "Pine-needles";
    std::cout << "Food Item name: " << getItem() << std::endl;
    setPos(posStruct(4, 5));
    std::cout << "getPos: (" << getPosition().xPos << "," << getPosition().yPos << ")" << std::endl;
    setColor(colorStruct(0.44, 1.0, 0.0));
    std::cout << "getColor: RGB(" << getColor().red << "," << getColor().green << "," << getColor().blue << ")" << std::endl;
    std::cout << std::boolalpha << isMushroom() << std::endl;
}



/**
 * testing function for WoodItem
 */
void WaterItem::testWaterItem(){

    std::cout << "Water Item Before:" << this << std::endl;
    setName("River Water");
    //getters
    std::cout << "Water name: " << getItem() << std::endl;
    std::cout << "getPos: (" << getPosition().xPos << "," << getPosition().yPos << ")" << std::endl;
    std::cout << "getColor: RGB(" << getColor().red << "," << getColor().green << "," << getColor().blue << ")" << std::endl;
    std::cout << std::boolalpha << isMushroom() << std::endl;

    name = "Distilled Water";
    std::cout << "Water name: " << getItem() << std::endl;
    setPos(posStruct(2, 1));
    std::cout << "getPos: (" << getPosition().xPos << "," << getPosition().yPos << ")" << std::endl;
    setColor(colorStruct(0.0, 0.0, 0.3));
    std::cout << "getColor: RGB(" << getColor().red << "," << getColor().green << "," << getColor().blue << ")"
              << std::endl;
    std::cout << std::boolalpha << isMushroom() << std::endl;
}
