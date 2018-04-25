#ifndef graphics_h
#define graphics_h

#include "Player.h"

#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet
void init(void);

// Initialize OpenGL Graphics
void InitGL(void);

// Callback functions for GLUT */

// Draw the window - this is where all the GL actions are
void display(void);

// Trap and process alphanumeric keyboard events
void kbd(unsigned char key, int x, int y);

// Trap and process special keyboard events
void kbdS(int key, int x, int y);

// Handle "mouse cursor moved" events 
void cursor(int x, int y);

// Calls itself after a specified time
void timer(int extra);

// Handle mouse button pressed and released events
void mouse(int button, int state, int x, int y);

/**
 * Requires: ColorStruct, PosStruct
 * Modifies: None
 * Effects: Draws a square with the given parameters
*/
void drawSquare(colorStruct color, posStruct pos, double wdth, double lgth);

/**
 * Requires: ColorStruct, PosStruct
 * Modifies: None
 * Effects: Draws a square with arms (to denote the player) with the given parameters
*/
void drawPlayer(colorStruct color, posStruct pos, double wdth, double lgth);

void drawItems();

#endif /* graphics_h */