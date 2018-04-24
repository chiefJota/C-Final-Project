#include "Tent.h"

Tent::Tent() {
    color = colorStruct(0,1,0);
    pos = posStruct(10,10);
}

Tent::Tent(colorStruct color, posStruct pos) {
    this->color = color;
    this->pos = pos;
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

// Text I/O Streams
std::ostream &operator << (std::ostream &outs, const Tent &t) {
    // Write variables
    outs << "Tent: "
         << t.curDay << " "
         << t.curTime << " "
         << t.startTime << " "
         << t.pos.xPos << " "
         << t.pos.yPos << " "
         << t.color.red << " "
         << t.color.green << " "
         << t.color.blue << " ";

//    // Write Array
//    for(int i = t.items.size()-1; i >= 0; i--) {
//        // Pull object from pointer
//        // Sort
//        if(t.items[i]->getItem().find("Water") != std::string::npos) {
//            // Water object
//            // Build object
//            WaterItem piece;
//            piece.setName(t.items[i]->getItem());
//            piece.setPoison(t.items[i]->isMushroom());
//            piece.setColor(colorStruct(t.items[i]->getColor().red,t.items[i]->getColor().green,t.items[i]->getColor().blue));
//            piece.setPos(posStruct(t.items[i]->getPosition().xPos,t.items[i]->getPosition().yPos));
//
//            // Send the object
//            // Add item to save
//            outs << piece << " ";
//        } else {
//            // Food object
//            // Build object
//            FoodItem piece;
//            piece.setName(t.items[i]->getItem());
//            piece.setPoison(t.items[i]->isMushroom());
//            piece.setColor(colorStruct(t.items[i]->getColor().red,t.items[i]->getColor().green,t.items[i]->getColor().blue));
//            piece.setPos(posStruct(t.items[i]->getPosition().xPos,t.items[i]->getPosition().yPos));
//
//            // Send the object
//            // Add item to save
//            outs << piece << " ";
//        }
//    }

    // Return the out stream
    return outs;
}

std::istream &operator >> (std::istream &ins, Tent t) {
    // Remove name from text
    std::string name;
    ins >> name;

    // Assign easy variables
    ins >> t.curDay;
    ins >> t.curTime;
    ins >> t.startTime;

    // Build position struct
    int x;
    int y;
    ins >> x;
    ins >> y;

    // Assign position struct
    t.pos = posStruct(x,y);

    // Build color struct
    double r;
    double g;
    double b;
    ins >> r;
    ins >> g;
    ins >> b;

    // Assign position struct
    t.color = colorStruct(r,g,b);

    // Return the in stream
    return ins;
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