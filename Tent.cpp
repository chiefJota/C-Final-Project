//
// Created by Workstation2 on 4/10/2018.
//

#include "Tent.h"
#include "Items.h"
#include "Player.h"
Tent::Tent() {
    color = colorStruct(0,1,0);
    pos = posStruct(10,10);

}

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
    std::cout<<"Tent class testing"<< std::endl;
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
    std::cout<<"Tick is a bool which returns true if it is greater than 0 (should be true): " << tick() << std::endl;
    std::cout<<"Getting the current time should be one second less than 90 (should be 89): " << getCurrentTime() << std::endl;
    
}