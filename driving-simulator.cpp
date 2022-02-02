#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<cstring>
#include <GL/glut.h>
#include <time.h>

#define MAXSPEED 20.0
#define COEFF 1
#define pi (2*acos(0.0))

//double cameraHeight;
//double angle;
//double map_angle;
//double Block_size = 40;
//double Block_distance = 38, size_cube = 38;
//int slices_spehere = 30, stacks_spehere = 30;
//int segments_cylinder = 24;
//double temp = 0;
//double move_pos = 2;
//double ar = 0;

double cameraAngle;
int drawgrid;
int drawaxes;
double car = 0;
double X = 10, Y = 50, Z = 10;
double x_font = 12.0, y_font = 35.0;
float lx=0.0f,lz=-1.0f; // actual vector representing the camera's direction
double leftRightMove = 0;
double sky = -1000;
double speed = 0.0;
time_t oldTime;


struct point {
    double x, y, z;
};

struct car_coord { // considered as square and not cube
    point fl, // front-left
    fr, // front-right
    bl, // back-left
    br; // back-right
};

void output(double x, double y, char *string) {
//set the position of the text in the window using the x, y coordinates
    glRasterPos2f(x, y);
//get the length of the string to display
    int len = (int) strlen(string);

//loop to display character by character
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
    }
}

//point l, u, r;
car_coord coord_car;

void drawAxes() {
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

void drawMainCar() {
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

void drawBackground() {
    glPushMatrix();{
        glTranslatef(0,sky,500);
        glRotatef(90,0,0,1);
        glColor3f(.3,0.9,.9);
        glScalef(.003,2,1);
        glutSolidCube(1000);
    }glPopMatrix();
}

void drawHill() {
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

void display() {
    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(.345, 0.4, 0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************
        camera setup
    ********************/

    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    gluLookAt(0,Y,10,	0+lx,-99999999999, 0+lz,	0,0,1);

    glMatrixMode(GL_MODELVIEW);

    car -= speed;
    Y -= speed;
    sky -= speed;
    speed *= 0.98;

    std::string s = "speed : " + std::to_string(speed);
    s.pop_back();s.pop_back();s.pop_back();s.pop_back();s.pop_back();
    char *str = &s[0];
    y_font -= speed;

    output(x_font, y_font, str);

    if(abs(car) <= 1500) {
        for(int i = 0, j = 0; i <= 10; i++, j += 200) {
            if(i <= 5) {
                glPushMatrix();{
                    glTranslatef(-120,-j,0);
                    glPushMatrix();{
                        glTranslatef(0,0,0);
                        glColor3f(.6,.6,.6);
                        glRotatef(90,1,0,0);
                        glutSolidCube(50);
                    }glPopMatrix();

                    glPushMatrix();{
                        glTranslatef(0,0,20);
                        glColor3f(.6,.6,0);
                        glutSolidCone(40,30,30,40);
                    }glPopMatrix();
                }glPopMatrix();
            } else {
                glPushMatrix();{
                    glTranslatef(-120,-j,0);
                    glPushMatrix();{
                        glColor3f(0,1,0);
                        glutSolidCone(20,30,20,20);
                    }glPopMatrix();

                    glPushMatrix();{
                        glColor3f(.5,.5,.3);
                        glScalef(.01,.4,5);
                        glutSolidSphere(7,10,10);
                    }glPopMatrix();
                }glPopMatrix();
            }
        }

        for(int i = 0, j = 0; i <= 10; i++, j += 200) {
            if(i <= 4) {
                glPushMatrix();{
                    glColor3f(.345,.78,0);
                    glTranslatef(80,-j,-15);
                    glTranslatef(0,55,0);
                    glutSolidSphere(9,5,5);
                }glPopMatrix();

                glPushMatrix();{
                    glTranslatef(120,-j,0);
                    glPushMatrix();{
                        glTranslatef(0,0,0);
                        glColor3f(.6,.6,.6);
                        glRotatef(90,1,0,0);
                        glutSolidCube(50);
                    }glPopMatrix();

                    glPushMatrix();{
                        glTranslatef(0,0,20);
                        glColor3f(1,.6,0);
                        glutSolidCone(40,30,30,40);
                    }glPopMatrix();
                }glPopMatrix();
            } else if (i == 5) {
                glPushMatrix();{
                    glTranslatef(120,-j,0);
                    glPushMatrix();{
                        glColor3f(.5,.5,.3);
                        glScalef(.01,.4,5);
                        glutSolidSphere(7,10,10);
                    }glPopMatrix();

                    glPushMatrix();{
                        glTranslatef(5,0,1);
                        glColor3f(0,.5,.3);
                        glutSolidSphere(10,10,10);
                    }glPopMatrix();

                    glPushMatrix();{
                        glTranslatef(-5,0,1);
                        glColor3f(0,.5,.3);
                        glutSolidSphere(10,10,10);
                    }glPopMatrix();

                    glPushMatrix();{
                        glTranslatef(0,0,20);
                        glColor3f(0,.5,.2);
                        glutSolidSphere(15,10,10);
                    }glPopMatrix();
                }glPopMatrix();
            } else {
                glPushMatrix();{
                    glTranslatef(120,-j,0);
                    glPushMatrix();{
                        glColor3f(0,1,0);
                        glutSolidCone(20,30,20,20);
                    }glPopMatrix();

                    glPushMatrix();{
                        glColor3f(.5,.5,.3);
                        glScalef(.01,.4,5);
                        glutSolidSphere(7,10,10);
                    }glPopMatrix();
                }glPopMatrix();
            }
        }

        drawRoad();
        drawRoadMiddle();

    } else if (abs(car) <= 2000) {
        for(int i = 0, j = 0; i <= 15; i++, j += 200) {
            glPushMatrix();
            glTranslatef(-120,-j,0);
            glPushMatrix();
            glColor3f(0,1,0);
            glutSolidCone(20,30,20,20);
            glPopMatrix();

            glPushMatrix();
            glColor3f(.5,.5,.3);
            glScalef(.01,.4,5);
            glutSolidSphere(7,10,10);
            glPopMatrix();
            glPopMatrix();
        }

        for(int i = 0, j = 0; i <= 15; i++, j += 200) {
            glPushMatrix();
            glTranslatef(120,-j,0);
            glPushMatrix();{
                glTranslatef(0,0,0);
                glColor3f(.6,.6,.6);
                glRotatef(90,1,0,0);
                glutSolidCube(50);
            }glPopMatrix();

            glPushMatrix();{
                glTranslatef(0,0,20);
                glColor3f(1,.6,0);
                glutSolidCone(40,30,30,40);
            }glPopMatrix();
            glPopMatrix();
        }

        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);

        glBegin(GL_POLYGON);
        glVertex3f(-2,0,-30);
        glVertex3f(2,0,-30);
        glVertex3f(-2,-2500,-30);
        glVertex3f(2,-2500,-30);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);

        glBegin(GL_POLYGON);
        glVertex3f(100,-1000,-30);
        glVertex3f(-100,-1000,-30);
        glVertex3f(-100,-2700,-30);
        glVertex3f(100,-2700,-30);
        glEnd();
        glPopMatrix();
    } else {
        for(int i = 0, j = 2200; i <= 10; i++, j += 100) {
            glPushMatrix();
            glTranslatef(-120,-j,0);
            glPushMatrix();{
                glTranslatef(0,0,0);
                glColor3f(.6,.6,.6);
                glRotatef(90,1,0,0);
                glutSolidCube(50);
            }glPopMatrix();

            glPushMatrix();{
                glTranslatef(0,0,20);
                glColor3f(.6,.6,0);
                glutSolidCone(40,30,30,40);
            }glPopMatrix();
            glPopMatrix();
        }

        for(int i = 0, j = 2200; i <= 10; i++, j += 100) {
            glPushMatrix();
            glTranslatef(120,-j,0);
            glPushMatrix();{
                glTranslatef(0,0,0);
                glColor3f(.6,.6,.6);
                glRotatef(90,1,0,0);
                glutSolidCube(50);
            }glPopMatrix();

            glPushMatrix();{
                glTranslatef(0,0,20);
                glColor3f(1,.6,0);
                glutSolidCone(40,30,30,40);
            }glPopMatrix();
            glPopMatrix();
        }

        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);

        glBegin(GL_POLYGON);
        glVertex3f(-2,-1800,-30);
        glVertex3f(2,-1800,-30);
        glVertex3f(-2,-4000,-30);
        glVertex3f(2,-4000,-30);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.245, 0.245, 0.245);

        glBegin(GL_POLYGON);
        glVertex3f(100,-2000,-30);
        glVertex3f(-100,-2000,-30);
        glVertex3f(-100,-4000,-30);
        glVertex3f(100,-4000,-30);
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0,0,3);

        glBegin(GL_POLYGON);
        glVertex3f(-2,0,-30);
        glVertex3f(2,0,-30);
        glVertex3f(-2,-1700,-30);
        glVertex3f(2,-1700,-30);
        glEnd();
        glPopMatrix();
    }

    drawMainCar();
    drawBackground();
    drawHill();
    glutSwapBuffers();
}

void animate() {
    //angle += 0.05;
    glutPostRedisplay();

    //TODO Update pos x of car
    //  Using equation speed = distance / time ?
    //  To get time :
    /*
    static int nb = 0;
    time_t temp = time(NULL);
    unsigned long secondes = (unsigned long) difftime(temp, oldTime);
    if(secondes >= 1){
        oldTime = temp;
        ++nb;
        //printf("%i\n", nb);
    }
     */

    //printf("car=[%f, %f, %f]\n", coord_car.bl.x, coord_car.bl.y, coord_car.bl.z);

    /* Collision detection */

    // in specialKeyListener

}

void init() {
    drawgrid = 0;
    drawaxes = 1;
    //cameraHeight = 150.0;
    cameraAngle = 1.0;
    //angle = 0;

    coord_car.fl.x = 17;
    coord_car.fl.y = -130;
    coord_car.fl.z = -30;

    coord_car.fr.x = -17;
    coord_car.fr.y = -130;
    coord_car.fr.z = -30;

    coord_car.bl.x = 17;
    coord_car.bl.y = -60;
    coord_car.bl.z = -30;

    coord_car.br.x = -17;
    coord_car.br.y = -60;
    coord_car.br.z = -30;



    /*
    u.x = 0;
    u.y = 0;
    u.z = 1;

    r.x = -1/sqrt(2);
    r.y = 1/sqrt(2);
    r.z = 0;

    l.x = -1/sqrt(2);
    l.y = -1/sqrt(2);
    l.z = 0;
    */

    //map_angle = 90;

    oldTime = time(NULL);

    //clear the screen
    glClearColor(0, 0, 0, 0);

    /************************
    / set-up projection here
    ************************/

    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(80, 1,	1, 30000.0);
}
double acceleration (double speed_x) {
    double ret;
    if (speed_x == MAXSPEED)
        return speed_x;

    if (speed_x < 3) {
        ret = speed_x + 0.5*COEFF;
    } else if (speed_x < 8) {
        ret = speed_x + 0.3*COEFF;
    } else if (speed_x < 13) {
        ret = speed_x + 0.2*COEFF;
    } else if (speed_x < 16) {
        ret = speed_x + 0.1*COEFF;
    } else {
        ret = speed_x + 0.07*COEFF;
        if (speed_x > MAXSPEED)
            ret = 20.0;
    }

    return ret;
}

double deceleration(double speed_x) {
    double ret;
    if (speed_x > 0.08) {
        ret = (speed_x * 0.95);
    } else {
        ret += speed_x - 0.2 * COEFF;
        if (ret < -5.0)
            return -5.0;
    }
    return ret;
}

void specialKeyListener(int key, int x,int y) {
    double alpha = 1.5;
    switch(key) {
        case GLUT_KEY_DOWN:
            /*if((coord_car.bl.y >= 0) || (coord_car.br.y >= 0)){
                speed = 0;
                break;
            }*/

            speed = deceleration(speed);
            car += speed;
            Y += speed;
            X += speed;
            {
                if (speed > -4.9)
                    sky += 5 * (abs(speed) / 5);
                else
                    sky -= 5;
            }
            break;

        case GLUT_KEY_UP:
            /*if((coord_car.bl.y <= -2500) || (coord_car.br.y <= -2500)){
                speed = 0;
                break;
            }*/

            speed = acceleration(speed);

            car -= speed;
            Y -= speed;
            X -= speed;

            sky -= speed;
            y_font -= speed;

            break;

        case GLUT_KEY_RIGHT:
            if(coord_car.fr.x <= -100){
                speed = 0;
                break;
            }

            glRotatef(1, 0.0, 1.0, 0.0);
            glRotatef(1, 0.0, -1.0, 0.0);
            glTranslatef(2.0, 0.0, 0.0);

            leftRightMove -= 0.5;
            //cameraAngle += 0.03;

            coord_car.fl.x -= alpha;
            coord_car.fr.x -= alpha;
            coord_car.bl.x -= alpha;
            coord_car.br.x -= alpha;

            break;

        case GLUT_KEY_LEFT:
            if(coord_car.fl.x >= 100){
                speed = 0;
                break;
            }

            leftRightMove += 0.5;
            //cameraAngle -= 0.03;

            coord_car.fl.x += alpha;
            coord_car.fr.x += alpha;
            coord_car.bl.x += alpha;
            coord_car.br.x += alpha;

            break;


        //UP AND DOWN -> mouvement de la caméra
        case GLUT_KEY_PAGE_UP :

            cameraAngle += 0.03;
            lx = sin(cameraAngle);
            lz = -cos(cameraAngle);
            break;

        case GLUT_KEY_PAGE_DOWN :
            cameraAngle -= 0.03;
            lx = sin(cameraAngle);
            lz = -cos(cameraAngle);
            break;

        //case GLUT_KEY_INSERT:
            //glutLeaveMainLoop();

    }


    /*
    if (speed > 0)
        std::cout << "vitesse : " << speed << std::endl;
    else
        std::cout << "vitesse en arrière : " << abs(speed) << std::endl;
    */
}

int main(int argc, char **argv){
    glutInit(&argc,argv);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow("car driving test");

    init();

    glEnable(GL_DEPTH_TEST);
    /*glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_CLAMP);*/

    glutDisplayFunc(display);
    glutIdleFunc(animate);

    //glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    //glutMouseFunc(mouseListener);

    glutMainLoop();

    return 0;
}