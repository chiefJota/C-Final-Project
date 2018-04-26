//
// Created by Workstation2 on 4/10/2018.
//

#include "Items.h"

//default constructor
Item::Item() {

}

//non default constructor
Item::Item(std::string name, colorStruct color, posStruct pos) {
    this->name = name;
    this->color = color;
    this->pos = pos;
}


//default constructor for FoodItem
FoodItem::FoodItem(){

    //three seeds for each FoodItem
    srand(randSeeds[1]);
    srand(randSeeds[2]);
    srand(randSeeds[3]);

    int windowW = 500;
    int windowH = 500;

    name = "Food";
    this->color = colorStruct(0,0,1);
    this->pos = posStruct(rand() % windowW, rand() % windowH);

    int MIN_CHANCE = 1;
    int MAX_CHANCE = 100;

    int poisonChance = rand() % MAX_CHANCE + MIN_CHANCE;

    if (poisonChance < 25){
        isPoisonous = true;
    }
    else{
        isPoisonous= false;
    }
}

//non default constructor for FoodItem
FoodItem::FoodItem(std::string n, colorStruct color, posStruct pos) {
    name = n;
    this->color = color;
    this->pos = pos;

    /*
    * Random 1 to 100
    * if Random <= 25
    *      isPoisonous = true
    * else
    *      isP = false
    */

    //three seeds for each FoodItem
    srand(randSeeds[1]);
    srand(randSeeds[2]);
    srand(randSeeds[3]);

    int MIN_CHANCE = 1;
    int MAX_CHANCE = 100;

    int poisonChance = rand() % MAX_CHANCE + MIN_CHANCE;

    if (poisonChance < 25){
        isPoisonous = true;
    }
    else{
        isPoisonous= false;
    }
}

/**
 * Getters for FoodItem
 */
std::string FoodItem::getItem() const {
    return name;
}

posStruct FoodItem::getPosition() const {
    return  pos;
}

colorStruct FoodItem::getColor() const {
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

void FoodItem::setPoison(bool poison) {
    isPoisonous = poison;
}

/**
 * isMushroom method
 */
bool::FoodItem::isMushroom() const {
    return isPoisonous;
}

/**
 * Text I/O Streams
 */
std::ostream &operator << (std::ostream &outs, const FoodItem &item) {
    // Convert Name
    std::string outName = item.getItem();
    for(int i = 0; i < outName.length(); i++) {
        if(outName[i] == ' ') {
            outName[i] = '_';
        }
    }

    // Write variables
    outs << "FoodItem: "
         << outName << " "
         << item.isMushroom() << " "
         << item.getPosition().xPos << " "
         << item.getPosition().yPos << " "
         << item.getColor().red << " "
         << item.getColor().green << " "
         << item.getColor().blue;

    // Return the out stream
    return outs;
}

std::istream &operator >> (std::istream &ins, FoodItem &item) {
    // Remove name from text
    std::string name;
    ins >> name;

    // Assign easy variables
    std::string inName;
    bool inPoison;
    ins >> inName;
    ins >> inPoison;
    item.setName(inName);
    item.setPoison(inPoison);

    // Build position struct
    int x;
    int y;
    ins >> x;
    ins >> y;

    // Assign position struct
    item.setPos(posStruct(x,y));

    // Build color struct
    double r;
    double g;
    double b;
    ins >> r;
    ins >> g;
    ins >> b;

    // Assign position struct
    item.setColor(colorStruct(r,g,b));

    // Return the in stream
    return ins;
}

//default constructor for WaterItem
WaterItem::WaterItem(){

    //three seeds for each WaterItem
    srand(randSeeds[4]);
    srand(randSeeds[5]);
    srand(randSeeds[6]);

    int windowW = 500;
    int windowH = 500;

    name = "Water";
    this->color = colorStruct(0,0,1);
    this->pos = posStruct(rand() % windowW, rand() % windowH);

    int MIN_CHANCE = 1;
    int MAX_CHANCE = 100;

    int poisonChance = rand() % MAX_CHANCE + MIN_CHANCE;

    if (poisonChance < 25){
        isPoisonous = true;
    }
    else{
        isPoisonous= false;
    }
}

//no default constructor for WaterItem
WaterItem::WaterItem(std::string n, colorStruct color, posStruct pos) {
    name = n;
    this->color = color;
    this->pos = pos;

    //three seeds for each WaterItem
    srand(randSeeds[4]);
    srand(randSeeds[5]);
    srand(randSeeds[6]);

    int MIN_CHANCE = 1;
    int MAX_CHANCE = 100;

    int poisonChance = rand() % MAX_CHANCE + MIN_CHANCE;

    if (poisonChance < 25){
        isPoisonous = true;
    }
    else{
        isPoisonous= false;
    }
}

/**
 * Getters for WaterItem
 */
std::string WaterItem::getItem() const {
    return name;
}

posStruct WaterItem::getPosition() const {
    return pos;
}

colorStruct WaterItem::getColor() const {
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

void WaterItem::setPoison(bool poison) {
    isPoisonous = poison;
}

/**
 * isMushroom method for WaterItem
 * @return
 */
bool ::WaterItem::isMushroom() const {
    return isPoisonous;
}

/**
 * Text I/O Streams
 */
std::ostream &operator << (std::ostream &outs, const WaterItem &item) {
    // Convert Name
    std::string outName = item.getItem();
    for(int i = 0; i < outName.length(); i++) {
        if(outName[i] == ' ') {
            outName[i] = '_';
        }
    }

    // Write variables
    outs << "WaterItem: "
         << outName << " "
         << item.isMushroom() << " "
         << item.getPosition().xPos << " "
         << item.getPosition().yPos << " "
         << item.getColor().red << " "
         << item.getColor().green << " "
         << item.getColor().blue;

    // Return the out stream
    return outs;
}

std::istream &operator >> (std::istream &ins, WaterItem &item) {
    // Remove name from text
    std::string name;
    ins >> name;

    // Assign easy variables
    std::string inName;
    bool inPoison;
    ins >> inName;
    ins >> inPoison;
    item.setName(inName);
    item.setPoison(inPoison);

    // Build position struct
    int x;
    int y;
    ins >> x;
    ins >> y;

    // Assign position struct
    item.setPos(posStruct(x,y));

    // Build color struct
    double r;
    double g;
    double b;
    ins >> r;
    ins >> g;
    ins >> b;

    // Assign position struct
    item.setColor(colorStruct(r,g,b));

    // Return the in stream
    return ins;
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

    setName("Distilled Water");
    std::cout << "Water name: " << getItem() << std::endl;
    setPos(posStruct(2, 1));
    std::cout << "getPos: (" << getPosition().xPos << "," << getPosition().yPos << ")" << std::endl;
    setColor(colorStruct(0.0, 0.0, 0.3));
    std::cout << "getColor: RGB(" << getColor().red << "," << getColor().green << "," << getColor().blue << ")"
              << std::endl;
    std::cout << std::boolalpha << isMushroom() << std::endl;
}
