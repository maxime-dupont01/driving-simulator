#ifndef _LIBRARY_H
#define _LIBRARY_H

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <cstring>
#include <GL/freeglut.h>
#include <time.h>
#include <array>
#include <vector>
#include <stdio.h>
#include <irrKlang.h> // for sound
#include "./irrKlang/conio.h" //same

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_W_H_RUN 900
#define pi (2*acos(0.0))

using namespace irrklang;
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

// The different windows
extern int winMenu, winGuide, winRun  /*, winTrackSelection, trackSelection*/;

extern ISoundEngine* soundEngine; //for sound
extern ISoundEngine* soundEngine_effets; //for sound for effets

struct point {
    double x, y, z;
};

struct car_coord { // considered as square and not cube
    point fl, // front-left
    fr, // front-right
    bl, // back-left
    br; // back-right
};

struct keys_use {
    bool IS_KEY_UP = false,
    IS_KEY_DOWN = false,
    IS_KEY_LEFT = false,
    IS_KEY_RIGHT = false;
};

/* Menu */
void renderMenu();
void mouseMenu(int button, int state, int x, int y);

/*Track */
/*
void renderTrackSelection();
void mouseTrackSelection(int button, int state, int x, int y);
*/

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
void specialUpListener(int key, int x, int y);


void acceleration (double &speed_x);
double deceleration (double speed_x);


/* Draw */
void drawCircle(double radius, int segments);
void drawBarrier();
void drawObstacle();
void drawMainCar(double leftRightMove, double car);
void drawBackground(double sky);
void drawHill(double sky);

void drawLine(std::pair<double,double> p1, std::pair<double, double> p2, std::pair<double, double> p3, double z);

void drawPolygonsFromVectors(std::vector<std::pair<double,double>> v, double z, double r, double g, double b);

std::pair<double, double> drawBezierGeneralized(std::array<std::array<double, 2>,4> PT, double t);

void drawBezier(std::array<double, 2> p1, std::array<double, 2> p2, std::array<double, 2> p3, std::array<double, 2> p4,
                std::array<double, 2> p5, std::array<double, 2> p6, std::array<double, 2> p7, std::array<double, 2> p8,
                double z, double r, double g, double b, std::vector<std::pair<double, double>>& ret);

void drawRoadBezier(std::array<double, 2> p1, std::array<double, 2> p2, std::array<double, 2> p3, std::array<double, 2> p4,
                    std::array<double, 2> p5, std::array<double, 2> p6, std::array<double, 2> p7, std::array<double, 2> p8,
                    std::vector<std::pair<double, double>>& roads, std::vector<std::pair<double, double>>& middle_roads);


/* Odometer */
void HUD(double speed);
void drawHUD(double speed);

#endif
