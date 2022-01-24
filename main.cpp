#define GL_GLEXT_PROTOTYPES
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string>
using namespace std;

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

// The coordinates for the vertices of the cube and rotation
double x = 0.4;
double y = 0.4;
double z = 0.4;
double rX = 0;
double rY = 0;

// The different windows
int win1, win2;

void printText(GLfloat x, GLfloat y, string text) {
    glPushMatrix();
    glTranslatef(x,y,0);
    for (int i=0; i<text.length(); i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }
    glPopMatrix();
}

void renderMenu(void) {
    glClearColor(0.0, 0.0, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(3.0); // Width for stroke text (1 by default)

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 2500, 0, 2500);

    printText(1100,2300,"Menu");

    glLineWidth(1.0);
    printText(100,1400,"* Start game");
    printText(100,1200,"* Change... ");
    printText(100,1000,"* Quit");
    printText(100,800,"* Credits");

    glutSwapBuffers();
}

void renderCube() {

    // Set Background Color
    glClearColor(0.4, 0.4, 0.4, 1.0);

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Rotate when user changes rX and rY
    glRotatef(rX, 1.0, 0.0, 0.0);
    glRotatef(rY, 0.0, 1.0, 0.0);

    // BACK
    glBegin(GL_TRIANGLES);
    glColor3f(0.4, 0.3, 0.5);
    glVertex3f(x, y, z);
    glVertex3f(x, -y, z);
    glVertex3f(-x, y, z);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 0.3, 0.2);
    glVertex3f(-x, -y, z);
    glVertex3f(x, -y, z);
    glVertex3f(-x, y, z);
    glEnd();

    // FRONT
    // Using 4 trianges!
    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.5, 0.3);
    glVertex3f(-x, y, -z);
    glVertex3f(0, 0, -z);
    glVertex3f(-x, -y, -z);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.5, 0.0);
    glVertex3f(-x, -y, -z);
    glVertex3f(0, 0, -z);
    glVertex3f(x, -y, -z);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.3, 0.3);
    glVertex3f(-x, y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(0, 0, -z);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(0, 0, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, -y, -z);
    glEnd();

    // LEFT
    glBegin(GL_TRIANGLES);
    glColor3f(0.3, 0.5, 0.6);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glVertex3f(-x, y, -z);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-x, y, z);
    glVertex3f(-x, -y, z);
    glVertex3f(-x, y, -z);
    glEnd();

    // RIGHT
    glBegin(GL_TRIANGLES);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(x, y, z);
    glVertex3f(x, y, -z);
    glVertex3f(x, -y, z);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(x, -y, -z);
    glVertex3f(x, y, -z);
    glVertex3f(x, -y, z);
    glEnd();

    // TOP
    glBegin(GL_TRIANGLES);
    glColor3f(0.6, 0.0, 0.0);
    glVertex3f(x, y, z);
    glVertex3f(x, y, -z);
    glVertex3f(-x, y, -z);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.6, 0.1, 0.2);
    glVertex3f(-x, y, z);
    glVertex3f(x, y, z);
    glVertex3f(-x, y, -z);
    glEnd();

    // BOTTOM
    glBegin(GL_TRIANGLES);
    glColor3f(0.4, 0.0, 0.4);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glVertex3f(x, -y, z);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.3, 0.0, 0.3);
    glVertex3f(x, -y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(x, -y, z);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

static void keyboardCube(unsigned char Key, int x, int y){
    switch(Key){
        case 27: // Escape key
            glutHideWindow();
            glutSetWindow(win1);
            glutShowWindow();
            break;
    }
}
static void specialKeyboardCube(int Key, int x, int y){
    switch (Key) {
        case GLUT_KEY_RIGHT:
            rY += 15;
            break;
        case GLUT_KEY_LEFT:
            rY -= 15;
            break;
        case GLUT_KEY_DOWN:
            rX -= 15;
            break;
        case GLUT_KEY_UP:
            rX += 15;
            break;
    }

    // Request display update
    glutPostRedisplay();
}

void mouseMenu(int button, int state, int x, int y) {
    if ((state == GLUT_DOWN) && (button == GLUT_LEFT_BUTTON)){
        if( (x > 100) && (x < 400) && (y > 305) && (y < 345) ) {
            //Start game
            glutHideWindow();
            glutSetWindow(win2);
            glutShowWindow();
        } else if( (x > 100) && (x < 200) && (y > 368) && (y < 403) ) {
            //Change...
        } else if( (x > 100) && (x < 200) && (y > 430) && (y < 460) ) {
            //Quit
            glutLeaveMainLoop();
        } else if( (x > 100) && (x < 200) && (y > 490) && (y < 520) ) {
            //Credits
        }
    }
    //printf("x=%i / y=%i\n", x, y);
}

/*
void reshapeMenu(int w,int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,w,0,h);
    glScalef(1,-1,1);
    glTranslatef(0,-h,0);
    glMatrixMode(GL_MODELVIEW);
}
 */

int main(int argc, char **argv) {

    // Initialize GLUT and process user parameters
    glutInit(&argc, argv);

    // Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);

    // Window and callback functions for Menu
    win1 = glutCreateWindow("Menu");
    glutDisplayFunc(renderMenu);
    //glutReshapeFunc(reshapeMenu);
    glutMouseFunc(mouseMenu);

    // Window and callback functions for Cube
    win2 = glutCreateWindow("Cube");
    glEnable(GL_DEPTH_TEST); // Enable Z-buffer depth test
    glutDisplayFunc(renderCube);
    glutSpecialFunc(specialKeyboardCube);
    glutKeyboardFunc(keyboardCube);

    glutHideWindow();

    glutMainLoop();

    return 0;
}