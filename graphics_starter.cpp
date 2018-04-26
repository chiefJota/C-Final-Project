#include <vector>
#include <ctime>
#include <regex>
#include <fstream>
#include "Items.h"
#include "graphics.h"
#include "Tent.h"

using namespace std;

// IMPORTANT: Make sure the path to GLUT matches your system as I have it installed in a different directory because of how my computer is configured.

// Global Graphics variables
GLdouble width = 500;
GLdouble height = 500;
int wd;
std::vector<std::unique_ptr<Item>> ItemsList;
int mouseX;
int mouseY;
double itemWidth = 8;
double itemHeight = 8;
double playerWidth = 20;
double playerHeight = 25;
double tentWidth = 40;
double tentHeight = 40;
bool showAlert = false;
string alertText;

// Global Data Variables
Player player(colorStruct(0.85,0,0),posStruct((int)width/2,(int)height/2));
Tent tent(colorStruct(0,1,0),posStruct((int)width/2,(int)height/2));
int curDay;
string saveFileName;
bool collectedAllItems;
bool dayIsOver;
bool tripMode;

// Initial Startup
// Sets the Global Graphic variables
void init() {
//    // Set window size // Now done above
//    width = 500;
//    height = 500;

    // Set day handlers
    collectedAllItems = false;
    dayIsOver = false;
    tripMode = false;

    // Set Alert
    alertText = " ";

    // Set Save File
    saveFileName = "hikeSave.txt";

    // Set Day listener
    curDay = tent.getDay()-1;

    //initialize random generator
    srand(time(NULL));

    // Check for new day
    if(curDay != tent.getDay()) {

        //resize the vector of items
        //ItemsList.resize(6);
        std::vector<int> randNums = {rand() % (int)width, rand() % (int)height, rand() % (int)width, rand() % (int)height, rand() % (int)width, rand() % (int)height, rand() % (int)width, rand() % (int)height, rand() % (int)width, rand() % (int)height, rand() % (int)width, rand() % (int)height};

        //Populates vector of items with FoodItems and the position is random
        ItemsList.push_back(std::make_unique<FoodItem>("Berries", colorStruct(1.0,0.0,0.0),posStruct(randNums[0],randNums[1])));
        ItemsList.push_back(std::make_unique<FoodItem>("Rocks", colorStruct(0.0,0.06,0.46),posStruct(randNums[2],randNums[3])));
        ItemsList.push_back(std::make_unique<FoodItem>("Mysterious Flesh", colorStruct(0.83,0.71,0.55),posStruct(randNums[4],randNums[5])));

        //Populates vector of items with WaterItems
        ItemsList.push_back(std::make_unique<WaterItem>("River Water", colorStruct(0.0,0.0,1.0),posStruct(randNums[6],randNums[7])));
        ItemsList.push_back(std::make_unique<WaterItem>("Four Loko", colorStruct(0.0,0.3,0.8),posStruct(randNums[8],randNums[9])));
        ItemsList.push_back(std::make_unique<WaterItem>("Distilled Water", colorStruct(0.0,0.1,0.95),posStruct(randNums[10],randNums[11])));
    }
}

// Initialize OpenGL Graphics
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.3f, 0.5f, 0.4f, 0.0f);
}

// Handler for window-repaint event. Call back when the window first appears and
// whenever the window needs to be re-painted.
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);

    // Chooses the drawing mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Check if all items non-poison items are collected
    bool foundItem = false;
    for(std::unique_ptr<Item> &item : ItemsList) {
        // Check if it's a mushroom (poisoned)
        if(!item->isMushroom()) {
            // Not a mushroom, So non-mushroom items are still in play
            foundItem = true;
        }
    }

    // Check if non-poison items exist
    if(!foundItem) {
        // No items were found, all items collected
        collectedAllItems = true;
        triggerAlert("All items collected!");
    }

    // Check for the day being over
    if(collectedAllItems && dayIsOver) {
        // Day is over, Go to new day
        // Turn off trip mode
        tripMode = false;

        // TODO: Continue to next day
    } else if(dayIsOver) {
        // Day is over, Not all items collected
        // TODO: Game over screen because day ended before all items collected
    }

    // --- Draw Start
    // Draw Tent
    drawSquare(tent.getColor(),tent.getPos(),tentWidth,tentHeight);

    // Draw Player
    drawPlayer(player.getColor(),player.getPos(),playerWidth,playerHeight);

    // --- Draw Items
    drawItems();

    // Check for overlap with Items
    for(std::unique_ptr<Item> &item : ItemsList) {
        // Check position
        if(isTouchingItem(posStruct(mouseX,mouseY),item->getPosition())) {
            // Check if mushroom
            if(item->isMushroom()) {
                // Overlapped
                drawText_Center("Poison",item->getPosition().xPos,item->getPosition().yPos);
            } else {
                // Overlapped
                drawText_Center(item->getItem(),item->getPosition().xPos,item->getPosition().yPos);
            }
        }
    }

    // Draw Alert Text
    if(showAlert) {
        drawAlert();
        alertTimer(0);
    }

    // Render trigger
    glFlush();
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    switch(key) {
        // Escape
        case 27:
            // Save Game
            if(!saveGame(saveFileName)) {
                // Save Failed
                triggerAlert("Failed to save data please try again.");
            } else {
                triggerAlert("Saved the game.");
            }

            // Quit Game
            glutDestroyWindow(wd);
            exit(0);

        // t
        case 116:
            // Save Game
            if(!saveGame(saveFileName)) {
                // Save Failed
                triggerAlert("Failed to save data please try again.");
            } else {
                triggerAlert("Saved the game.");
            }
            break;

        // y
        case 121:
            // Load Game
            if(!loadGame(saveFileName)) {
                // Load Failed
                triggerAlert("Failed to load data please try again.");
            } else {
                triggerAlert("Loaded your save.");
            }
            break;

        // w
        case 119:
            // Check if trip mode
            if(!tripMode) {
                // Not trip Mode
                // Move Player
                player.move(moveDirection::up);
            } else {
                // trip Mode
                // Move Player
                player.move(moveDirection::down);
            }
            break;

        // a
        case 97:
            // Check if trip mode
            if(!tripMode) {
                // Not trip Mode
                // Move Player
                player.move(moveDirection::left);
            } else {
                // trip Mode
                // Move Player
                player.move(moveDirection::right);
            }
            break;

        // s
        case 115:
            // Check if trip mode
            if(!tripMode) {
                // Not trip Mode
                // Move Player
                player.move(moveDirection::down);
            } else {
                // trip Mode
                // Move Player
                player.move(moveDirection::up);
            }
            break;

        // d
        case 100:
            // Check if trip mode
            if(!tripMode) {
                // Not trip Mode
                // Move Player
                player.move(moveDirection::right);
            } else {
                // trip Mode
                // Move Player
                player.move(moveDirection::left);
            }
            break;

        // e
        case 101:
            // Check if touching tent
            if(isShapeTouchingShape(player.getPos(),playerWidth,playerHeight,tent.getPos(),tentWidth,tentHeight)) {
                // Check if player can go to next day
                if(collectedAllItems) {
                    // Next day
                    // Go to next day
                    dayIsOver = true;
                } else {
                    // Can't go to next day
                    triggerAlert("There are more items out there!");
                }
            } else {
                // Collect Item
                // Loop through all items
                int index = 0;
                for (std::unique_ptr<Item> &item : ItemsList) {
                    // Check for collision with item
                    if(isShapeTouchingShape(player.getPos(),playerWidth,playerHeight,item->getPosition(),itemWidth,itemHeight)) {
                        // Touching
                        // Check if mushroom or regular item
                        if(item->isMushroom()) {
                            // Mushroom Item
                            // Enable trip mode
                            tripMode = true;
                        }

                        // Remove item from the list
                        ItemsList.erase(std::remove(ItemsList.begin(),ItemsList.end(),item),ItemsList.end());

                        // Break the loop
                        break;
                    }

                    // Iterate
                    index++;
                }
            }
            break;
    }

    glutPostRedisplay();

    return;
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            // Check if trip mode
            if(!tripMode) {
                // Not trip Mode
                // Move Player
                player.move(moveDirection::down);
            } else {
                // trip Mode
                // Move Player
                player.move(moveDirection::up);
            }
            break;
        case GLUT_KEY_LEFT:
            // Check if trip mode
            if(!tripMode) {
                // Not trip Mode
                // Move Player
                player.move(moveDirection::left);
            } else {
                // trip Mode
                // Move Player
                player.move(moveDirection::right);
            }
            break;
        case GLUT_KEY_RIGHT:
            // Check if trip mode
            if(!tripMode) {
                // Not trip Mode
                // Move Player
                player.move(moveDirection::right);
            } else {
                // trip Mode
                // Move Player
                player.move(moveDirection::left);
            }
            break;
        case GLUT_KEY_UP:
            // Check if trip mode
            if(!tripMode) {
                // Not trip Mode
                // Move Player
                player.move(moveDirection::down);
            } else {
                // trip Mode
                // Move Player
                player.move(moveDirection::up);
            }
            break;
    }

    glutPostRedisplay();

    return;
}

void cursor(int x, int y) {
    // Set mouse pos
    mouseX = x;
    mouseY = y;

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    glutPostRedisplay();
}

void timer(int extra) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

void alertTimer(int extra) {
    glutPostRedisplay();
    glutTimerFunc(680, hideAlert, 0);
}

// Draw Function to create a square
void drawSquare(colorStruct color, posStruct pos, double wdth, double lgth) {
    // Set Color
    glColor3f(color.red, color.green, color.blue);

    // Begin Draw
    glBegin(GL_QUADS);

    // Top Left
    glVertex2i(pos.xPos-(wdth/2.0), pos.yPos-(lgth/2.0));

    // Top Right
    glVertex2i(pos.xPos+(wdth/2.0), pos.yPos-(lgth/2.0));

    // Bottom Right
    glVertex2i(pos.xPos+(wdth/2.0), pos.yPos+(lgth/2.0));

    // Bottom Left
    glVertex2i(pos.xPos-(wdth/2.0), pos.yPos+(lgth/2.0));

    // End Draw
    glEnd();
}

// Draw Function to create player squares
void drawPlayer(colorStruct color, posStruct pos, double wdth, double lgth) {
    // Draw normal square
    drawSquare(color,pos,wdth,lgth);

    // Draw Head
    drawSquare(colorStruct(0.83,0.71,0.55),pos,15,15);
}

void drawItems(){

    //draw items
    for(int i=0; i < ItemsList.size(); i++){
        //manipulate output to display nicely
        colorStruct color = ItemsList[i]->getColor();
        posStruct pos = ItemsList[i]->getPosition();

        //draw em
        drawSquare(color,pos,itemWidth,itemHeight);
    }

   // ItemsList.clear();
}

void triggerAlert(const std::string &text) {
    alertText = text;
    showAlert = true;
}

void drawAlert() {
    // Set Color
    glColor3f(1,1,1);

    // Get Center
    GLint textCenter = (width/2)-getTextCenter(GLUT_BITMAP_TIMES_ROMAN_24,alertText);

    // Draw
    glRasterPos2i(textCenter,36);
    for (char c : alertText) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
}

void hideAlert(int num) {
    showAlert = false;
}

GLint getTextCenter(void* font, const std::string &text) {
    GLint textCenter = 0;
    for(char c : text) {
        textCenter += glutBitmapWidth(font,c);
    }
    return (textCenter/2);
}

// Checks to see if Point A is inside the bounds of Point B
bool isTouchingItem(const posStruct &toucher, const posStruct &item) {
    return (toucher.xPos >= item.xPos-(itemWidth/2.0) && // Left side
            toucher.xPos <= item.xPos+(itemWidth/2.0) && // Right side
            toucher.yPos >= item.yPos-(itemHeight/2.0) && // Top
            toucher.yPos <= item.yPos+(itemHeight/2.0)); // Bottom
}

// Checks to see if two defined shapes ('a' and 'b') are touching within any of their bounds
bool isShapeTouchingShape(const posStruct &a, double aWidth, double aHeight, const posStruct &b, double bWidth, double bHeight) {
    return !(b.xPos+(bWidth/2.0) < a.xPos-(aWidth/2.0) ||
             a.xPos+(aWidth/2.0) < b.xPos-(bWidth/2.0) ||
             b.yPos-(bHeight/2.0) > a.yPos+(aHeight/2.0) ||
             a.yPos-(aHeight/2.0) > b.yPos+(bHeight/2.0));
}

void drawText_Center(const string &text, int textX, int textY) {
    // Variable
    auto font = GLUT_BITMAP_TIMES_ROMAN_24;

    // Display String
    std::string message = text;
    glColor3f(1,0,0);

    // Set Position
    GLint txtX = textX-getTextCenter(font,message);
    GLint txtY = textY-itemHeight;
    if(txtX < 10) {
        // Outside on left
        txtX = 0;
    }
    GLint textLength = 0;
    for(char c : text) {
        textLength += glutBitmapWidth(font,c);
    }
    if(txtX > width-(textLength+1)) {
        // Outside on right
        txtX = width-textLength;
    }
    if(txtY < 25) {
        // Outside on top
        txtY = 25;
    }
    glRasterPos2i(txtX,txtY);

    // Draw String
    for (char c : message) {
        glutBitmapCharacter(font,c);
    }
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();

    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Camping Survival"); // Title
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}

// Saves the current player states to a text file.
// Returns false if failed
bool saveGame(const string &fileName) {
    // Write Data Out
    // Open Out File
    ofstream fOut;
    fOut.open(fileName);

    // Check for out Out File open
    if(fOut) {
        // Write Player and Tent to file
        fOut << player << "\n";
        fOut << tent << "\n";
    } else {
        // Out File did not open
        return false;
    }

    // Close the Out File
    fOut.close();

    return true;
}

// Load the current player states from a text file.
// Returns false if failed
bool loadGame(const string &fileName) {
    // Write Data In
    // Open In File
    ifstream fIn;
    fIn.open(fileName);

    // Check for In File open
    if(fIn) {
        // Write to objects
        fIn >> player;
        fIn >> tent;
    } else {
        // In File did not open
        return false;
    }

    // Close the In File
    fIn.close();

    return true;
}