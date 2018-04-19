//
// Created by Workstation2 on 4/10/2018.
//

#include "Tent.h"

Tent::Tent() {
    color = colorStruct(0,1,0);
    pos = posStruct(10,10);
}

//this method is not feasible until graphics portion
//double getItems(std::vector<std::unique_ptr<Item>> &items){
//    sort items into food and water items, not possible till graphics portion
//}

//this method is used in graphics portion to call next day method when tent is clicked
void Tent::mouse(int button, int state, int x, int y){
    goToNextDay();
}

void Tent::goToNextDay() {
    curDay++;
    //set new starting point to countdown from
    startTime = startTime - (curDay * 10);
}

int Tent::getDay(){
    return curDay;
}

posStruct Tent::getPos() const {
    return pos;
}

colorStruct Tent::getColor() const {
    return color;
}

void Tent::setTime(double startTime){
    curTime = startTime;
}
bool Tent::tick(){
    curTime--;
    return curTime > 0;
}

double Tent::getCurrentTime(){
    return curTime;
}

void Tent::testTent() {
    std::cout<<"Tent class testing:\n"<< std::endl;
    //starting day should be 0
    std::cout<<"Starting Day Count (should be 0): " << getDay() <<std::endl;
    //set the time as startime
    setTime(startTime);
    //Output the current time allowed per day
    std::cout<<"Time allowed for day (should be 100): " << getCurrentTime() <<std::endl;
    //mouse interaction is not available until graphics portion
    std::cout<<"Go forward a day to the first day." <<std::endl;
    goToNextDay();
    //should output as day 1
    std::cout<<"Current Day (should be 1): " << getDay() << std::endl;
    //start time should be changed and we will set it and get it
    setTime(startTime);
    std::cout<<"Time allowed for day (should be 90): " << getCurrentTime() <<std::endl;
    //tick method should be used for graphics time iterator but to show that it works...
    std::cout<<"Tick is a bool which returns true if it is greater than 0 (should be 1 (true)): " << tick() << std::endl;
    std::cout<<"Getting the current time should be one second less than 90 (should be 89): " << getCurrentTime() << std::endl;
    //test getters with temporary struct values
    std::cout<<"Getting color and position (Position should be 10,10), (Color should be green (0,1,0)) : " << std::endl;
    std::cout << "getPos: (" << getPos().xPos << "," << getPos().yPos << ")" << std::endl;
    std::cout << "getColor: RGB(" << getColor().red << "," << getColor().green << "," << getColor().blue << ")\n" << std::endl;
}