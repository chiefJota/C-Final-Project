//
// Created by Workstation2 on 4/10/2018.
//

#include "Items.h"

#include <regex>

Item::Item() {

}

Item::Item(std::string &name, colorStruct color, posStruct pos) {
    name = " ";
    this->color = color;
    this->pos = pos;
}



FoodItem::FoodItem(){

}

FoodItem::FoodItem(std::string &n, colorStruct color, posStruct pos) {
    name = n;
    this->color = color;
    this->pos = pos;
}


std::string FoodItem::getItem() {
    return name;
}

posStruct FoodItem::getPosition() {
    return  pos;
}

colorStruct FoodItem::getColor() {
    return color;
}


std::string FoodItem::setName(std::string food) {
    name = food;
}
colorStruct FoodItem::setColor(colorStruct Color) {
    color = Color;
}

posStruct FoodItem::setPos(posStruct position) {
    pos = position;
}

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


WaterItem::WaterItem(){

}

WaterItem::WaterItem(std::string &n, colorStruct color, posStruct pos) {
    name = n;
    this->color = color;
    this->pos = pos;
}

std::string WaterItem::getItem() {
    return name;
}

posStruct WaterItem::getPosition() {
    return pos;
}

colorStruct WaterItem::getColor() {
    return color;
}

std::string WaterItem::setName(std::string water) {
    name = water;
}

posStruct WaterItem::setPos(posStruct position) {
    pos = position;
}

colorStruct WaterItem::setColor(colorStruct Color) {
    color = Color;
}

bool::WaterItem::isMushroom() {

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
