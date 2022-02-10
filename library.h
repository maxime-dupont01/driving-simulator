#ifndef _LIBRARY_H
#define _LIBRARY_H

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <cstring>
#include <GL/freeglut.h>
#include <time.h>
#include <array>

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
constexpr int factorial(int n);
float binomial_coff(float n,float k);


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
void drawLine(std::array<double, 2> p1, std::array<double, 2> p2, std::array<double, 2> p3, double z);
std::array<double, 2> drawBezierGeneralized(std::array<std::array<double, 2>,4> PT, double t, double z_);
void drawBezier(std::array<double, 2> p1, std::array<double, 2> p2, std::array<double, 2> p3, std::array<double, 2> p4,
                std::array<double, 2> p5, std::array<double, 2> p6, std::array<double, 2> p7, std::array<double, 2> p8,
                double z, double r, double g, double b);
void drawRoadBezier(std::array<double, 2> p1, std::array<double, 2> p2, std::array<double, 2> p3, std::array<double, 2> p4);

/* Odometer */
void HUD(double speed);
void drawHUD(double speed);

#endif
