#include <vector>
#include <ctime>
#include <regex>
#include <string>
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
bool showAlert = false;
string alertText = "";


// Global Data Variables
Player player(colorStruct(0.85,0,0),posStruct((int)width/2,(int)height/2));
Tent tent(colorStruct(0,1,0),posStruct((int)width/2,(int)height/2));
int curDay;
string saveFileName;

// Initial Startup
// Sets the Global Graphic variables
void init() {
//    // Set window size // Now done above
//    width = 500;
//    height = 500;

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
        for (int i= 0; i < randNums.size(); ++i) {
            std::cout << randNums[i] << std::endl;
        }

        //Populates vector of items with FoodItems and the position is random
        ItemsList.push_back(std::make_unique<FoodItem>("Berries", colorStruct(1.0,0.0,0.0),posStruct(rand() % int(width),rand() % int(height))));
        ItemsList.push_back(std::make_unique<FoodItem>("Rocks", colorStruct(0.0,0.06,0.46),posStruct(rand() % int(width),rand() % int(height))));
        ItemsList.push_back(std::make_unique<FoodItem>("Mysterious Flesh", colorStruct(0.83,0.71,0.55),posStruct(rand() % int(width),rand() % int(height))));

        //Populates vector of items with WaterItems
        ItemsList.push_back(std::make_unique<WaterItem>("River Water", colorStruct(0.0,0.0,1.0),posStruct(rand() % int(width),rand() % int(height))));
        ItemsList.push_back(std::make_unique<WaterItem>("Four Loko", colorStruct(0.0,0.3,0.8),posStruct(rand() % int(width),rand() % int(height))));
        ItemsList.push_back(std::make_unique<WaterItem>("Distilled Water", colorStruct(0.0,0.1,0.95),posStruct(rand() % int(width),rand() % int(height))));

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


    // --- Draw Start
    // Draw Tent
    drawSquare(tent.getColor(),tent.getPos(),40,40);

    // Draw Player
    drawPlayer(player.getColor(),player.getPos(),20,25);

    // --- Draw Items
    drawItems();

    // Check for overlap with Items
    for(std::unique_ptr<Item> &item : ItemsList) {
        // Check position
        if(isTouchingItem(posStruct(mouseX,mouseY),item->getPosition())) {
            // Check if mushroom
            if(item->isMushroom()) {
                // Overlapped
                // Display String
                std::string message = "Poisoned!";
                glColor3f(1,0,0);

                // Set Position
                GLint txtX = item->getPosition().xPos-45;
                GLint txtY = item->getPosition().yPos-itemHeight;
                if(txtX < 10) {
                    // Outside on left
                    txtX = 0;
                }
                if(txtY < 25) {
                    // Outside on top
                    txtY = 25;
                }
                glRasterPos2i(txtX,txtY);

                // Draw String
                for (char c : message) {
                    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                }
            } else {
                // Overlapped
                // Display String
                std::string message = item->getItem();
                glColor3f(1,0,0);

                // Set Position
                GLint txtX = item->getPosition().xPos-getTextCenter(GLUT_BITMAP_TIMES_ROMAN_24,message);
                GLint txtY = item->getPosition().yPos-itemHeight;
                if(txtX < 10) {
                    // Outside on left
                    txtX = 0;
                }
                if(txtY < 25) {
                    // Outside on top
                    txtY = 25;
                }
                glRasterPos2i(txtX,txtY);

                // Draw String
                for (char c : message) {
                    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
                }
            }
        }
    }

    // Draw Alert Text
    if(showAlert) {
        drawAlert();
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
            player.move(moveDirection::up);
            break;

        // a
        case 97:
            player.move(moveDirection::left);
            break;

        // s
        case 115:
            player.move(moveDirection::down);
            break;

        // d
        case 100:
            player.move(moveDirection::right);
            break;
    }

    glutPostRedisplay();

    return;
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            player.move(moveDirection::down);
            break;
        case GLUT_KEY_LEFT:
            player.move(moveDirection::left);
            break;
        case GLUT_KEY_RIGHT:
            player.move(moveDirection::right);
            break;
        case GLUT_KEY_UP:
            player.move(moveDirection::up);
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

GLint getTextCenter(void* font, const std::string &text) {
    GLint textCenter = 0;
    for(char c : text) {
        textCenter += glutBitmapWidth(font,c);
    }
    return (textCenter/2);
}

// Checks to see if Point A is inside the bounds of Point B
bool isTouchingItem(const posStruct &pointA, const posStruct &pointB) {
    return (pointA.xPos >= pointB.xPos-(itemWidth/2.0) && // left side
            pointA.xPos <= pointB.xPos+(itemWidth/2.0) && // right side
            pointA.yPos >= pointB.yPos-(itemHeight/2.0) && // top
            pointA.yPos <= pointB.yPos+(itemHeight/2.0)); // bottom
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