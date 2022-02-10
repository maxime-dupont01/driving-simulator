#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <cstring>

#include "library.h"


/**** Menu *****/
void renderMenu() {
    glClearColor(0.0, 0.0, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(3.0); // Width for stroke text (1 by default)

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 2500, 0, 2500);

    printText(1100,2300,"Menu");

    glLineWidth(1.0);
    printText(100,1400,"* Play");
    printText(100,1200,"* Guide");
    printText(100,1000,"* Quit");
    printText(100,800,"* Credits");

    glutSwapBuffers();
}
void mouseMenu(int button, int state, int x, int y) {
    if ((state == GLUT_DOWN) && (button == GLUT_LEFT_BUTTON)){
        if( (x > 110) && (x < 200) && (y > 305) && (y < 345) ) {
            //Play
            glutHideWindow();
            glutSetWindow(winRun);
            glutShowWindow();
        } else if( (x > 110) && (x < 240) && (y > 368) && (y < 403) ) {
            //Guide
            glutHideWindow();
            glutSetWindow(winGuide);
            glutShowWindow();
        } else if( (x > 110) && (x < 200) && (y > 430) && (y < 460) ) {
            //Quit
            glutLeaveMainLoop();
        } else if( (x > 110) && (x < 200) && (y > 490) && (y < 520) ) {
            //Credits
        }
    }
    //printf("x=%i / y=%i\n", x, y);
}


/**** Guide *****/
void renderGuide() {
    glClearColor(0.0, 0.0, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(3.0); // Width for stroke text (1 by default)

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 3500, 0, 3500);

    printText(1600,3250,"Guide");

    glLineWidth(2.0);
    printText(300,2600,"How to play ? Drive with your keyboard !");

    glLineWidth(1.0);
    printText(100,1800,"- Up arrow : to advance and accelerate");
    printText(100,1600,"- Down arrow : to slow down and back up");
    printText(100,1400,"- Left arrow : to turn left");
    printText(100,1200,"- Right arrow : to turn right");

    printText(300,300,"[ Press Enter to go back to the Menu ]");


    glutSwapBuffers();
}
void keyboardGuide(unsigned char Key, int x, int y){
    switch(Key){
        case 13: // Enter key
            glutHideWindow();
            glutSetWindow(winMenu);
            glutShowWindow();
            break;
    }
}


void stopReshape(int w, int h) {
    glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void printText(GLfloat x, GLfloat y, std::string text) {
    glPushMatrix();
    glTranslatef(x,y,0);
    for (int i=0; i<text.length(); i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }
    glPopMatrix();
}
void output(double x, double y, char *string) {
    //set the position of the text in the window using the x, y coordinates
    glRasterPos2f(x, y);
    //get the length of the string to display
    int len = (int)strlen(string);

    //loop to display character by character
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}

constexpr int factorial(int n) {
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);
    return n;
}

float binomial_coff(float n,float k) {
    float ans;
    ans = factorial(n) / (factorial(k)*factorial(n-k));
    return ans;
}


///**********       Draw       **********////

/*
void drawAxes(drawaxes) {
    if (drawaxes == 1) {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);{
            glVertex3f( 100,0,0);
            glVertex3f(-100,0,0);

            glVertex3f(0,-100,0);
            glVertex3f(0, 100,0);

            glVertex3f(0,0, 100);
            glVertex3f(0,0,-100);
        }glEnd();
    }
}
*/

void drawSquare(double a) {
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);{
        glVertex3f( a, a,0);
        glVertex3f( a,-a,0);
        glVertex3f(-a,-a,0);
        glVertex3f(-a, a,0);
    }glEnd();
}

void drawCircle(double radius, int segments) {
    int i;
    struct point points[100];

    glColor3f(1.0,0.0,1.0);

    //generates points
    for(i = 0; i <= segments; i++) {
        points[i].x = radius * cos(((double)i/(double)segments)*2*pi);
        points[i].y = radius * sin(((double)i/(double)segments)*2*pi);
    }

    //draw segments using generated points
    for(i = 0; i < segments; i++) {
        glBegin(GL_LINES);{
            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i+1].y,0);
        }glEnd();
    }
}

void drawBarrier() {
    glPushMatrix();
    glColor3f(0.184, 0.109, 0.13);

    glTranslatef(0,0,3);

    //Left one
    glBegin(GL_POLYGON);{
        glVertex3f(70,0,-30);
        glVertex3f(70,0,-20);

        glVertex3f(70,-2500,-20);
        glVertex3f(70,-2500,-30);
    }glEnd();

    //Right one
    glBegin(GL_POLYGON);{
        glVertex3f(-90,0,-30);
        glVertex3f(-90,0,-20);

        glVertex3f(-90,-2500,-20);
        glVertex3f(-90,-2500,-30);
    }glEnd();

    glPopMatrix();
}

void drawObstacle() {
    glPushMatrix();
    glColor3f(0.184, 0.109, 0.13);

    glTranslatef(0,0,3);

    //Front side
    glBegin(GL_QUADS);{
        glVertex3f( 3, -100,-30);
        glVertex3f( 3,-100,-10);
        glVertex3f(-3,-100,-10);
        glVertex3f(-3, -100,-30);
    }glEnd();

    //Top side
    glBegin(GL_QUADS);{
        glVertex3f( 3, -100,-10);
        glVertex3f( 3,-105,-10);
        glVertex3f(-3,-105,-10);
        glVertex3f(-3, -100,-10);
    }glEnd();

    glPopMatrix();
}

void drawTest() {
    glPushMatrix();
    glColor3f(0.184, 0.109, 0.13);

    glTranslatef(0,0,3);

    int nb1 = 1;
    int nb2 = -60;

    glBegin(GL_QUADS);{
        glVertex3f( 17, nb2,-30);
        glVertex3f( 17,nb2,-20);
        glVertex3f(17,nb2+30,-20);
        glVertex3f(17, nb2+30,-30);
    }glEnd();

    glPopMatrix();
}

void drawRoad() {
    glPushMatrix();
    glColor3f(0.245, 0.245, 0.245);

    glBegin(GL_POLYGON);{
        glVertex3f(100,0,-30);
        glVertex3f(-100,0,-30);

        glVertex3f(-100,-2500,-30);
        glVertex3f(100,-2500,-30);
    }glEnd();

    glPopMatrix();

    //drawBarrier();
    //drawObstacle();
    //drawTest();
}

void drawRoadMiddle() {
    glPushMatrix();
    glColor3f(1, 1, 1);

    glTranslatef(0,0,3);

    glBegin(GL_POLYGON);{
        glVertex3f(-2,0,-30);
        glVertex3f(2,0,-30);

        glVertex3f(-2,-2500,-30);
        glVertex3f(2,-2500,-30);
    }glEnd();

    glPopMatrix();
}

void drawMainCar(double leftRightMove, double car) {
    glPushMatrix();

    glTranslatef(leftRightMove, car, 0);
    glRotatef(90, 0, 0, 1);

    //lower part
    glPushMatrix();{
        glColor3f(1,.8,3);
        glScalef(2,1,.4);
        glutSolidCube(10);
    }glPopMatrix();

    //upper part
    glPushMatrix();{
        glTranslatef(0,0,4);
        glColor3f(.67,.67,.67);
        glScalef(1,1,.4);
        glutSolidCube(10);
    }glPopMatrix();

    //front wheel left part
    glPushMatrix();{
        glTranslatef(4,5,-2);
        glColor3f(1,.3,8);
        glScalef(2,.7,1);
        glutSolidSphere(2,100,100);
    }glPopMatrix();

    //front wheel right part
    glPushMatrix();{
        glTranslatef(-4,5,-2);
        glColor3f(1,0,1);
        glScalef(1,.7,1);
        glutSolidSphere(2,100,100);
    }glPopMatrix();

    //behind wheel left part
    glPushMatrix();{
        glTranslatef(4,-5,-2);
        glColor3f(1,.6,8);
        glScalef(1,.7,1);
        glutSolidSphere(2,100,100);
    }glPopMatrix();

    //behind wheel right part
    glPushMatrix();{
        glTranslatef(-4,-5,-2);
        glColor3f(1,.3,8);
        glScalef(1,.7,1);
        glutSolidSphere(2,100,100);
    }glPopMatrix();

    glPopMatrix();
}

void drawBackground(double sky) {
    glPushMatrix();{
        glTranslatef(0,sky,500);
        glRotatef(90,0,0,1);
        glColor3f(.3,0.9,.9);
        glScalef(.003,2,1);
        glutSolidCube(1000);
    }glPopMatrix();
}

void drawHill(double sky) {
    glPushMatrix();{
        glTranslatef(500,sky+30,0);
        glRotatef(90,0,0,1);
        glColor3f(0,0.9,0);
        glutSolidCone(200,400,20,20);
    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(-500,sky+30,0);
        glRotatef(90,0,0,1);
        glColor3f(0,0.9,0.5);
        glutSolidCone(200,400,20,20);
    }glPopMatrix();

    glPushMatrix();{
        glTranslatef(-700,sky+30,0);
        glRotatef(90,0,0,1);
        glColor3f(0,0.9,0.5);
        glutSolidCone(200,400,20,20);
    }glPopMatrix();
}

void drawLine(std::array<double, 2> p1, std::array<double, 2> p2, std::array<double, 2> p3, double z) {
    glBegin(GL_TRIANGLES);
    glVertex3f(p1[0], p1[1], z);
    glVertex3f(p2[0], p2[1], z);
    glVertex3f(p3[0], p3[1], z);
    glEnd();
    glFlush();
}

std::array<double, 2> drawBezierGeneralized(std::array<std::array<double, 2>,4> PT, double t, double z_) {

    double x = 0, y = 0, z = z_;

    for (int i = 0; i<4; i++) {
        x = x + binomial_coff((float)(4 /*number of points*/- 1), (float)i) * pow(t, (double)i) * pow((1 - t), (4 - 1 - i)) * PT[i][0];
        y = y + binomial_coff((float)(4 - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (4 - 1 - i)) * PT[i][1];
    }

    std::array<double, 2> ret;
    ret[0] = x;
    ret[1] = y;

    //std::cout << "ret " << ret[0] << " " << ret[1] << " " << ret[2] << std::endl;
    return ret;
}

void drawBezier(std::array<double, 2> p1, std::array<double, 2> p2, std::array<double, 2> p3, std::array<double, 2> p4,
                std::array<double, 2> p5, std::array<double, 2> p6, std::array<double, 2> p7, std::array<double, 2> p8,
                double z, double r, double g, double b){

    glColor3f(1,0,0);

    std::array<double, 2> p1_ = p1;
    std::array<double, 2> p5_ = p5;
    /* Draw each segment of the curve.Make t increment in smaller amounts for a more detailed curve.*/

    std::array<std::array<double, 2>,4> array1, array2;

    array1[0] = p1; array2[0] = p5;
    array1[1] = p2; array2[1] = p6;
    array1[2] = p3; array2[2] = p7;
    array1[3] = p4; array2[3] = p8;
    glColor3f(r,g,b);
    for(double t = 0.0;t <= 1.0; t += 0.02) {
        std::array<double, 2> p2_ = drawBezierGeneralized(array1, t, z);
        std::array<double, 2> p6_ = drawBezierGeneralized(array2,t, z);
        drawLine(p1_, p5_, p2_, z);
        drawLine(p5_, p2_, p6_, z);
        p1_ = p2_;
        p5_ = p6_;
    }

    glColor3f(r,g,b);
}

void drawRoadBezier(std::array<double, 2> p1, std::array<double, 2> p2, std::array<double, 2> p3, std::array<double, 2> p4) {
    std::array<double, 2> f1, f2, f3, f4;
    f1[0] = p1[0]; f1[1] = p1[1];
    f2[0] = p2[0]; f2[1] = p2[1];
    f3[0] = p3[0]; f3[1] = p3[1];
    f4[0] = p4[0]; f4[1] = p4[1];

    std::array<double, 2> g1, g2, g3, g4;
    g1[0] = p1[0]-200; g1[1] = p1[1];
    g2[0] = p2[0]-200; g2[1] = p2[1];
    g3[0] = p3[0]-200; g3[1] = p3[1];
    g4[0] = p4[0]-200; g4[1] = p4[1];

    drawBezier(f1, f2, f3, f4, g1, g2, g3, g4, -30.0, 0.245, 0.245, 0.245);

    f1[0] = p1[0]-98;
    f2[0] = p2[0]-98;
    f3[0] = p3[0]-98;
    f4[0] = p4[0]-98;

    g1[0] = p1[0]-102;
    g2[0] = p2[0]-102;
    g3[0] = p3[0]-102;
    g4[0] = p4[0]-102;
    drawBezier(f1, f2, f3, f4, g1, g2, g3, g4, -29.80, 1, 1, 1);

}

void HUD(double speed) {
    glTranslatef(-450, -450, 0);

    glColor3f(0.663, 0.663, 0.663); 
 
    GLUquadricObj *p = gluNewQuadric();
        
    gluDisk(p, 0, 100, 100, 100);
 
    //MARKINGS
    glTranslatef(0, 0, 0.5);
  
    glColor3f(0, 0, 0);
    gluDisk(p, 92, 100, 100, 100);

    glColor3f(0, 0.980, 0.604);
    gluPartialDisk(p, 70, 90, 100, 100, -120, 40);
    glColor3f(0.196, 0.804, 0.196);
    gluPartialDisk(p, 70, 90, 100, 100, -80, 40);
    glColor3f(0.604, 0.804, 0.196);
    gluPartialDisk(p, 70, 90, 100, 100, -40, 40);
    glColor3f(1, 0.843, 0);
    gluPartialDisk(p, 70, 90, 100, 100, 0, 40);
    glColor3f(1, 0.549, 0);
    gluPartialDisk(p, 70, 90, 100, 100, 40, 40);
    glColor3f(1, 0.271, 0);
    gluPartialDisk(p, 70, 90, 100, 100, 80, 40);
  
    float nt = 220;
    float nAngle = (200/1000.0) * (abs(speed*130));
  
    if (nAngle < 220) {
        nt = 220 - nAngle;
    } else {
        nt = 340;
    }    

    glColor3f(0, 0, 1);

    glLineWidth(5);

    glBegin(GL_LINES);{
        glVertex3f(1,0,0);
        glVertex3f(80*cos(nt*3.14/180),80*sin(nt*3.14/180),0.5);
    }glEnd();

    char speed_value[32];
    sprintf(speed_value, "%.0f", speed*22);
    glColor3f(0, 0, 0);
    glRasterPos3f(-20, 20 ,0);
    for(int i = 0; speed_value[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, speed_value[i]);
    }
}

void drawHUD(double speed) {
    // setup viewing projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(-550.0, 550.0, -550.0, 550.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    HUD(speed);

    //set 3D matrix mode back
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
