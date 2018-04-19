// Text Based Testing and File I/O
#include <fstream>

#include "Player.h"
#include "Tent.h"

using namespace std;

/*
 * How to use:
 * 1. Go to CMakeLists.txt
 * 2. Duplicate current 'add_executable(...)' line
 * 3. Comment out original 'add_executable(...)' line with '#'
 * 4. Remove '${SOURCE_FILES}' from new 'add_executable(...)' line
 * 5. Add 'textBased.cpp' to new 'add_executable(...)' line
 */

int main() {
    /// Variables
    string fileName = "saveData.txt";

    /// Create Objects
    // Create Player
    Player player(colorStruct(1,2,3),posStruct(4,5));

    // Create Items
    FoodItem foodItem;
    WaterItem waterItem;

    // Create Tent
    Tent tent;

    /// Class Testing
    cout << "Class Testing Start:" << endl;
    player.testFunctionality();
    cout << "-------------------" << endl;
    foodItem.testFoodItem();
    cout << "-------------------" << endl;
    waterItem.testWaterItem();
    cout << "-------------------" << endl;
    tent.testTent();
    cout << "-------------------" << endl;

    /// File I/O
    cout << "File I/O Start:" << endl;
    // Write Data Out
    // Open Out File
    ofstream fOut;
    fOut.open(fileName);

    // Check for out Out File open
    if(fOut) {
        // Out File opened
        cout << "Saved Data:" << endl;

        // Write to file
        fOut << player << "\n";
        cout << player << endl;

        fOut << foodItem << "\n";
        cout << foodItem << endl;

        fOut << waterItem << "\n";
        cout << waterItem << endl;

//        fOut << tent << "\n";
//        cout << tent << endl;
    } else {
        // Out File did not open
        return -1;
    }

    // Close the Out File
    fOut.close();

    // Write Data In
    // Open In File
    ifstream fIn;
    fIn.open(fileName);

    // Check for In File open
    if(fIn) {
        // In File opened
        cout << "Loaded Data:" << endl;

        // Write to objects
        Player player2;
        fIn >> player2;

        FoodItem foodItem2;
        fIn >> foodItem2;

        WaterItem waterItem2;
        fIn >> waterItem2;

//        Tent tent2;
//        fIn >> tent2;

        // Print objects to console
        cout << player2 << endl;
        cout << foodItem2 << endl;
        cout << waterItem2 << endl;
//        cout << tent2 << endl;

    } else {
        // In File did not open
        return -1;
    }

    // Close the In File
    fIn.close();

    // Exit
    return 0;
}