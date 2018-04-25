#include <vector>
#include <string>
#include "Items.h"
#include "graphics.h"
#include "Tent.h"



// IMPORTANT: Make sure the path to GLUT matches your system as I have it installed in a different directory because of how my computer is configured.

// Global Graphics variables
GLdouble width = 500;
GLdouble height = 500;
int wd;
std::vector<std::unique_ptr<Item>> ItemsList;


// Global Data Variables
Player player(colorStruct(0.85,0,0),posStruct((int)width/2,(int)height/2));
Tent tent(colorStruct(0,1,0),posStruct((int)width/2,(int)height/2));
int curDay;

// Initial Startup
// Sets the Global Graphic variables
void init() {
//    // Set window size // Now done above
//    width = 500;
//    height = 500;

    // Set Day listener
    curDay = tent.getDay()-1;
}

// Initialize OpenGL Graphics
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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

    // Check for new day
    if(curDay != tent.getDay()) {

        //Populates vector of items with FoodItems
        ItemsList.push_back(std::make_unique<FoodItem>("Berries", colorStruct(1.0,0.0,0.0),posStruct(150,200)));
        ItemsList.push_back(std::make_unique<FoodItem>("Rocks", colorStruct(0.0,0.06,0.46),posStruct(50,100)));
        ItemsList.push_back(std::make_unique<FoodItem>("Mysterious Flesh", colorStruct(0.83,0.71,0.55),posStruct(25,95)));

        //Populates vector of items with WaterItems
        ItemsList.push_back(std::make_unique<WaterItem>("River Water", colorStruct(0.0,0.0,1.0),posStruct(10,350)));
        ItemsList.push_back(std::make_unique<WaterItem>("Four Loko", colorStruct(0.0,0.0,1.0),posStruct(91,71)));
        ItemsList.push_back(std::make_unique<WaterItem>("Distilled Water", colorStruct(0.0,0.0,1.0),posStruct(60,9)));
    }

    // --- Draw Start
    // Draw Tent
    drawSquare(tent.getColor(),tent.getPos(),40,40);

    // Draw Player
    drawPlayer(player.getColor(),player.getPos(),20,25);

    // --- Draw Items
    drawItems();

    // Render trigger
    glFlush();
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    switch(key) {
        // Escape
        case 27:
            glutDestroyWindow(wd);
            exit(0);

        // w
        case 119:
            player.move(up);
            break;

        // a
        case 97:
            player.move(left);
            break;

        // s
        case 115:
            player.move(down);
            break;

        // d
        case 100:
            player.move(right);
            break;
    }

    glutPostRedisplay();

    return;
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            player.move(down);
            break;
        case GLUT_KEY_LEFT:
            player.move(left);
            break;
        case GLUT_KEY_RIGHT:
            player.move(right);
            break;
        case GLUT_KEY_UP:
            player.move(up);
            break;
    }

    glutPostRedisplay();

    return;
}

void cursor(int x, int y) {


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
        double wdth = 4;
        double lgth = 4;
        //draw em
        drawSquare(color,pos,wdth,lgth);
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
