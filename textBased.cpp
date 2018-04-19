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

    /// Class Testing
    // TODO: Implement class testing

    /// File I/O
    // TODO: Implement File I/O for Save and Load with all classes
    // Create Player
    Player player(colorStruct(1,2,3),posStruct(4,5));

    // Write Data Out
    // Open Out File
    ofstream fOut;
    fOut.open(fileName);

    // Check for out Out File open
    if(fOut) {
        // Out File opened
        // Write to file
        fOut << player << "\n";
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
        // Write to objects
        Player player2;
        fIn >> player2;

        // Print objects to console
        cout << player2 << endl;

    } else {
        // In File did not open
        return -1;
    }

    // Close the In File
    fIn.close();

    // Exit
    return 0;
}