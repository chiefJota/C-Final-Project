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

// Global Game Functions
enum GameState {mainMenu,playing,lostGame};
GameState gameState = mainMenu;

// Global Data Variables
Player player(colorStruct(0.85,0,0),posStruct((int)width/2,(int)height/2));
Tent tent(colorStruct(0,1,0),posStruct((int)width/2,(int)height/2));
int curDay;
string saveFileName;
bool collectedAllItems;
bool dayIsOver;
bool tripMode;
bool hoverStartBtn;
bool hoverLoadBtn;

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

    //initialize random generator
    srand(time(NULL));

    // Spawn Items
    generateItems();

    // Set up Day
    if(gameState == playing) {
        prepareGameToStart();
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

    // Check game state
    switch(gameState) {
        case mainMenu: {
            // Disable blending
            glDisable(GL_BLEND);

            // Define color
            colorStruct menuColor = colorStruct(1,1,1);

            // Draw Title Text
            string titleOfGame = "Trippy Hike";
            drawText_Center(titleOfGame,colorStruct(1,0,0),(width/2)-15,75);
            drawText_Center(titleOfGame,colorStruct(0,1,0),(width/2)+15,70);
            drawText_Center(titleOfGame,colorStruct(0,0,1),(width/2)-25,90);
            drawText_Center(titleOfGame,colorStruct(0,0,0),(width/2)+2,78);
            drawText_Center(titleOfGame,colorStruct(0,0,0),(width/2)+2,73);
            drawText_Center(titleOfGame,colorStruct(0,0,0),(width/2)-2,73);
            drawText_Center(titleOfGame,colorStruct(0,0,0),(width/2)-2,78);
            drawText_Center(titleOfGame,menuColor,width/2,75);

            // Draw Buttons
            int menuBtnWidth = 150;
            int menuBtnHeight = 50;

            if(isShapeTouchingShape(posStruct(mouseX,mouseY),5,5,posStruct(width/2,(height/2)-menuBtnHeight-10),menuBtnWidth,menuBtnHeight)) {
                drawButton("New Game",posStruct(width/2,(height/2)-menuBtnHeight-10),colorStruct(1,1,1),colorStruct(0,0,0),menuBtnWidth,menuBtnHeight);
                hoverStartBtn = true;
            } else {
                // It's hovering
                drawButton("New Game",posStruct(width/2,(height/2)-menuBtnHeight-10),colorStruct(0,0,0),colorStruct(1,1,1),menuBtnWidth,menuBtnHeight);
                hoverStartBtn = false;
            }

            if(isShapeTouchingShape(posStruct(mouseX,mouseY),5,5,posStruct(width/2,height/2),menuBtnWidth,menuBtnHeight)) {
                drawButton("Load Game",posStruct(width/2,height/2),colorStruct(1,1,1),colorStruct(0,0,0),menuBtnWidth,menuBtnHeight);
                hoverLoadBtn = true;
            } else {
                // It's hovering
                drawButton("Load Game",posStruct(width/2,height/2),colorStruct(0,0,0),colorStruct(1,1,1),menuBtnWidth,menuBtnHeight);
                hoverLoadBtn = false;
            }

            // Draw Controls
            drawText_Center("Controls:",menuColor,width/2,height-(24*5));
            drawText_Center("[Mouse Hover] Reveal Item Name",menuColor,width/2,height-(24*4));
            drawText_Center("[W/A/S/D] Move Character",menuColor,width/2,height-(24*3));
            drawText_Center("[E] Interact",menuColor,width/2,height-(24*2));
            drawText_Center("[ESC] Exit and Save Game",menuColor,width/2,height-24);
            break;
        }

        case playing: {
            // Check if trip mode is enabled
            if (tripMode) {
                // Enable blending
                glEnable(GL_BLEND);

                // Choose random
                if (rand() % 2) {
                    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
                } else {
                    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
                }
            } else {
                // Disable blending
                glDisable(GL_BLEND);
            }

            // Check if all items non-poison items are collected
            bool foundItem = false;
            for (std::unique_ptr<Item> &item : ItemsList) {
                // Check if it's a mushroom (poisoned)
                if (!item->isMushroom()) {
                    // Not a mushroom, So non-mushroom items are still in play
                    foundItem = true;
                }
            }

            // Check if non-poison items exist
            if (!foundItem) {
                // No items were found, all items collected
                collectedAllItems = true;
                triggerAlert("All items collected!");
            }

            // Check for the day being over
            if (collectedAllItems && dayIsOver) {
                // Day is over, Go to new day
                // Turn off trip mode
                tripMode = false;

                // Trigger Next Day
                tent.goToNextDay();

                // Spawn more items
                generateItems();

                // Reset for new day
                collectedAllItems = false;
                dayIsOver = false;

                // Start timer again
                curDay = tent.getDay();
                tent.setTime(tent.getStartTime());
            }

            // --- Draw Start
            // Draw Tent
            drawSquare(tent.getColor(), tent.getPos(), tentWidth, tentHeight);

            // Draw Player
            drawPlayer(player.getColor(), player.getPos(), playerWidth, playerHeight);

            // --- Draw Items
            drawItems();

            // Check for overlap with Items
            for (std::unique_ptr<Item> &item : ItemsList) {
                // Check position
                if (isTouchingItem(posStruct(mouseX, mouseY), item->getPosition())) {
                    // Check if mushroom
                    if (item->isMushroom()) {
                        // Overlapped
                        drawText_Center("Poison", colorStruct(1,0,0), item->getPosition().xPos, item->getPosition().yPos);
                    } else {
                        // Overlapped
                        drawText_Center(item->getItem(), colorStruct(1,1,1), item->getPosition().xPos, item->getPosition().yPos);
                    }
                }
            }

            // Tick the Tent's Day Timer
            if (!tent.tick()) {
                // Day is over, Not all items collected
                triggerAlert("You ran out of time.");
                gameState = lostGame;

            } else {
                // Day is continuing
                // Draw HUD
                drawHUD();
            }
            break;
        }

        case lostGame: {
            gameOverDisplay();
            break;
        }
    }

    // Draw Alert Text
    if (showAlert) {
        drawAlert();
//        alertTimer(0);
    }

    // Render trigger
    glFlush();
}

// Game is over
void gameOverDisplay(){
    // Do the text
    drawText_Center("You made it to Day "+to_string(tent.getDay()+1)+" and died.",colorStruct(1,1,1),width/2,(height/2)-24);
    drawText_Center("Click to continue.",colorStruct(1,1,1),width/2,(height/2)+24);

    // Color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // Check game state
    switch(gameState) {
        case mainMenu: {
            break;
        }

        case playing: {
            switch (key) {
                // Escape
                case 27:
                    // Save Game
                    if (!saveGame(saveFileName)) {
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
                    if (!saveGame(saveFileName)) {
                        // Save Failed
                        triggerAlert("Failed to save data please try again.");
                    } else {
                        triggerAlert("Saved the game.");
                    }
                    break;

                    // y
                case 121:
                    // Load Game
                    if (!loadGame(saveFileName)) {
                        // Load Failed
                        triggerAlert("Failed to load data please try again.");
                    } else {
                        triggerAlert("Loaded your save.");
                    }
                    break;

                    // w
                case 119:
                    // Check if trip mode
                    if (!tripMode) {
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
                    if (!tripMode) {
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
                    if (!tripMode) {
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
                    if (!tripMode) {
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
                    if (isShapeTouchingShape(player.getPos(), playerWidth, playerHeight, tent.getPos(), tentWidth,
                                             tentHeight)) {
                        // Check if player can go to next day
                        if (collectedAllItems) {
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
                            if (isShapeTouchingShape(player.getPos(), playerWidth, playerHeight, item->getPosition(),
                                                     itemWidth, itemHeight)) {
                                // Touching
                                // Check if mushroom or regular item
                                if (item->isMushroom()) {
                                    // Mushroom Item
                                    // Enable trip mode
                                    tripMode = true;
                                }

                                // Remove item from the list
                                ItemsList.erase(std::remove(ItemsList.begin(), ItemsList.end(), item), ItemsList.end());

                                // Break the loop
                                break;
                            }

                            // Iterate
                            index++;
                        }
                    }
                    break;
            }
            break;
        }

        case lostGame: {
            break;
        }
    }

    glutPostRedisplay();

    return;
}

void kbdS(int key, int x, int y) {
    switch(gameState) {
        case mainMenu: {
            break;
        }

        case playing: {
            switch (key) {
                case GLUT_KEY_DOWN:
                    // Check if trip mode
                    if (!tripMode) {
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
                    if (!tripMode) {
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
                    if (!tripMode) {
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
                    if (!tripMode) {
                        // Not trip Mode
                        // Move Player
                        player.move(moveDirection::up);
                    } else {
                        // trip Mode
                        // Move Player
                        player.move(moveDirection::down);
                    }
                    break;
            }
            break;
        }

        case lostGame: {
            break;
        }
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
    switch(gameState) {
        case mainMenu:
            // Check mouse clicks
            if(button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON) {
                // Check for hovers
                if(hoverStartBtn) {
                    tent.setDay(0);
                    player.setPlayerPos(width/2,height/2);
                    // Start game
                    // Switch game state
                    gameState = playing;

                    // Prepare the game
                    prepareGameToStart();
                } else if(hoverLoadBtn) {
                    // Start game and load
                    // Switch Game State
                    gameState = playing;

                    // Prepare the game
                    prepareGameToStart();

                    // Load Data
                    loadGame(saveFileName);
                }
            }
            break;

        case lostGame: {
            if(button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON) {
                // Relocate to main menu
                gameState = mainMenu;

                // Change background color
                glClearColor(0.3f, 0.5f, 0.4f, 0.0f);
            }
            break;
        }
    }

    glutPostRedisplay();
}

void timer(int extra) {
    // Check alert
    if(showAlert) {
        glutTimerFunc(680, hideAlert, 0);
    }

    // Do it
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

void drawText_Center(const string &text, const colorStruct &color, int textX, int textY) {
    // Variable
    auto font = GLUT_BITMAP_TIMES_ROMAN_24;

    // Display String
    std::string message = text;
    glColor3f(color.red,color.green,color.blue);

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

void drawHUD() {
    // Create Text
    ostringstream hudText;
    hudText << "Day " << (tent.getDay()+1) << ": " << fixed << std::setprecision(2) << (tent.getCurrentTime()/30);

    // Draw Timer
    drawText_Center(hudText.str(),colorStruct(1,1,1),width/2,height-10);
}

void drawButton(const std::string &text, const posStruct &pos, const colorStruct &textColor, const colorStruct &buttonColor, int buttonWidth, int buttonHeight) {
    drawSquare(buttonColor,pos,buttonWidth,buttonHeight);
    drawText_Center(text,textColor,pos.xPos,pos.yPos+(buttonHeight/3));
}

void prepareGameToStart() {
    // Set day handlers
    collectedAllItems = false;
    dayIsOver = false;
    tripMode = false;

    // Spawn Items
    generateItems();

    // Set Alert
    alertText = " ";

    // Set the current day
    curDay = tent.getDay();

    // Set the tent timer
    tent.setTime(tent.getStartTime());
}

void generateItems() {
    // Clear the ItemsList
    ItemsList.clear();

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

        // Write Item data
        for (std::unique_ptr<Item> &item : ItemsList) {
            fOut << "Item: " << item->getPosition().xPos << " " << item->getPosition().yPos << " " << item->isMushroom() << " \n";
        }
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

        // Check to see if save invalid
        if(tent.getCurrentTime() <= 0) {
            triggerAlert("Invalid Save");
            return false;
        }

        // Write to items
        for (std::unique_ptr<Item> &item : ItemsList) {
            string junk;
            fIn >> junk;

            int inX;
            int inY;
            fIn >> inX;
            fIn >> inY;
            item->setPos(posStruct(inX,inY));

            bool inPoison;
            fIn >> inPoison;
            item->setPoison(inPoison);
        }
    } else {
        // In File did not open
        return false;
    }

    // Close the In File
    fIn.close();

    return true;
}