#ifndef _LIBRARY_H
#define _LIBRARY_H

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <cstring>
#include <GL/freeglut.h>
#include <time.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_W_H_RUN 900
#define pi (2*acos(0.0))

// The different windows
extern int winMenu, winGuide, winRun;

struct point {
    double x, y, z;
};

struct car_coord { // considered as square and not cube
    point fl, // front-left
    fr, // front-right
    bl, // back-left
    br; // back-right
};


/* Menu */
void renderMenu();
void mouseMenu(int button, int state, int x, int y);

/* Guide */
void renderGuide();
void keyboardGuide(unsigned char Key, int x, int y);

void stopReshape(int w,int h);

void printText(GLfloat x, GLfloat y, std::string text);
void output(double x, double y, char *string);

/* Main application */
void display();
void animate();
void init();
void specialKeyListener(int key, int x,int y);
void keyboardListener(unsigned char Key, int x, int y);


double acceleration (double speed_x);
double deceleration(double speed_x);


/* Draw */
//void drawAxes();
void drawSquare(double a);
void drawCircle(double radius, int segments);
void drawBarrier();
void drawObstacle();
void drawTest();
void drawRoad();
void drawRoadMiddle();
void drawMainCar(double leftRightMove, double car);
void drawBackground(double sky);
void drawHill(double sky);


#endif