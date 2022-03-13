#include "library.h"

#include "Circuit.cpp"

#define MAXSPEED 30.0
#define COEFF 1
#define COEFF_TURN 1
#define PI (2*acos(0.0))

double car = 0;
double X = 10, Y = 50, Z = 10;
float lx=0.0f,lz=-1.0f; // actual vector representing the camera's direction
double leftRightMove = 0;
double sky = -1000;
double speed = 0.0;
time_t oldTime_fps;
time_t oldTime_enough;
time_t starting_time = time(nullptr);
unsigned long time_recorded = 0;
int fps = 0;
unsigned int state = 0; // different than 0 for shake camera

float turn = .01;
bool enoughTime = true;
int numberOfLaps = -1;

Circuit circuit;

// The different windows
int winMenu, winGuide, winRun;

//point l, u, r;
car_coord coord_car;

ISoundEngine* soundEngine; //for sound
ISoundEngine* soundEngine_effets; //for sound for effets

keys_use keys;

int main(int argc, char **argv){
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);

    // Window and callback functions for Menu
    winMenu = glutCreateWindow("Menu");
    glutDisplayFunc(renderMenu);
    glutReshapeFunc(stopReshape);
    glutMouseFunc(mouseMenu);
    //glutHideWindow();

    // Window and callback functions for Guide
    winGuide = glutCreateWindow("Guide");
    glutDisplayFunc(renderGuide);
    glutReshapeFunc(stopReshape);
    glutKeyboardFunc(keyboardGuide);
    glutHideWindow();

    // Main application
    glutInitWindowSize(WINDOW_W_H_RUN, WINDOW_W_H_RUN);
    winRun = glutCreateWindow("car driving test");
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutSpecialUpFunc(specialUpListener);
    //glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    glutHideWindow();

    init();

    // start the sound engines with default parameters
    soundEngine = createIrrKlangDevice();
    if (!soundEngine){
        printf("Could not startup soundEngine\n");
    }
    soundEngine_effets = createIrrKlangDevice();
    if (!soundEngine_effets){
        printf("Could not startup soundEngine for effects\n");
    }

    glEnable(GL_DEPTH_TEST);
    /*glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_CLAMP);*/

    glutMainLoop();

    /* End of programme */

    if(soundEngine) {
        soundEngine->drop(); // delete soundEngine
    }
    if(soundEngine_effets) {
        soundEngine_effets->drop(); // delete soundEngine effects
    }
    //glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

    return 0;
}

void display() {
    // get FPS :
    if (numberOfLaps >= 1) { //1 tour de circuit
        if (time_recorded == 0) {
            time_recorded = (unsigned long) difftime(time(nullptr), starting_time);
        }
        std::cout << "FINISHED ! in " << time_recorded << " seconds, not bad !\n";
        return;
    }
    ++fps;
    time_t temp = time(nullptr);
    auto diff_second = (unsigned long) difftime(temp, oldTime_fps);
    if(diff_second >= 1){
        oldTime_fps = temp;
        printf("FPS=%i\n", fps);
        fps = 0;
    }

    diff_second = (unsigned long) difftime(temp, oldTime_enough);
    if (diff_second >= 15) {
        oldTime_enough = temp;
        enoughTime = true;
    }
        //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(.7, 0.7, 1,0.7);	//color white/blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /********************
            camera setup
        ********************/

    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();


    // animation is case of collision -> shake the camera
    double delta = 0.3;
    switch (state) {
        case 0:
            gluLookAt(0,Y,10,	0+lx,-99999999999, 0+lz,	0,0,1);
            break;
        case 1:
            gluLookAt(delta,Y,10,	0+lx,-99999999999, 0+lz,	0,0,1);
            state = 2;
            break;
        case 2:
            gluLookAt(0,Y,10,	0+lx,-99999999999, 0+lz,	0,0,1);
            state = 3;
            break;
        case 3:
            gluLookAt(-delta,Y,10,	0+lx,-99999999999, 0+lz,	0,0,1);
            state = 4;
            break;
        case 4:
            gluLookAt(0,Y,10,	0+lx,-99999999999, 0+lz,	0,0,1);
            state = 5;
            break;
        case 5:
            gluLookAt(delta,Y,10,	0+lx,-99999999999, 0+lz,	0,0,1);
            state = 6;
            break;
        case 6:
            gluLookAt(0,Y,10,	0+lx,-99999999999, 0+lz,	0,0,1);
            state = 7;
            break;
        case 7:
            gluLookAt(-delta,Y,10,	0+lx,-99999999999, 0+lz,	0,0,1);
            state = 0;
            break;
    }

    glMatrixMode(GL_MODELVIEW);
    speed *= 0.98;
    if (enoughTime){
        if (circuit.isLapPassed()) {
            numberOfLaps++;
            std::cout << "number of lap(s) : " << numberOfLaps << "\n";
            enoughTime = false;
        }
    }
    circuit.shiftCircuit(speed);
    drawPolygonsFromVectors(circuit.roads, -30.0, 0.245, 0.245, 0.245);
    drawPolygonsFromVectors(circuit.middle_roads, -29.80, 1, 1, 1);

    drawMainCar(leftRightMove, car);
    /*
    drawBackground(sky);
    drawHill(sky);
    */
    drawHUD(speed);
    glutSwapBuffers();

}

void animate() {

    /*******************
         key listeners
      ******************/

    if(keys.IS_KEY_UP) {
        speed = acceleration(speed);
    }
    if(keys.IS_KEY_DOWN) {
        speed = deceleration(speed);
    }
    if(keys.IS_KEY_LEFT) {
        circuit.rotateCircuit(turn);
        circuit.rotateCircuit(-turn);
    }

    if(keys.IS_KEY_RIGHT) {
        circuit.rotateCircuit(-turn);
        circuit.rotateCircuit(turn);
    }

    double ratio = 20/sqrt(2);

    glutPostRedisplay();
}

void init() {
    circuit.generate_circuit(1);
    circuit.print();

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
            ret = MAXSPEED;
    }

    return ret;
}

double deceleration(double speed_x) {
    double ret;
    if (speed_x > 0.08) {
        ret = (speed_x * 0.95);
    } else {
        ret = speed_x - 0.2 * COEFF;
        if (ret < -5.0)
            ret = -5.0;
    }
    return ret;
}

void specialKeyListener(int key, int x,int y) {
    switch(key) {
        case GLUT_KEY_UP:
                keys.IS_KEY_UP = true;
            break;

        case GLUT_KEY_DOWN:
            keys.IS_KEY_DOWN = true;
            break;

        case GLUT_KEY_LEFT:
                keys.IS_KEY_LEFT = true;
            break;

        case GLUT_KEY_RIGHT:
                keys.IS_KEY_RIGHT = true;
            break;
        case GLUT_KEY_ALT_L: //debug affichage du circuit dans la console
                circuit.print();
            break;
    }
}

void specialUpListener(int key, int x, int y){
    switch(key){
        case GLUT_KEY_UP :
            keys.IS_KEY_UP = false;
            break;

        case GLUT_KEY_DOWN :
            keys.IS_KEY_DOWN = false;
            break;

        case GLUT_KEY_LEFT :
            keys.IS_KEY_LEFT = false;
            break;

        case GLUT_KEY_RIGHT :
            keys.IS_KEY_RIGHT = false;
            break;
    }
}

void keyboardListener(unsigned char Key, int x, int y){
    switch(Key){
        case 27: // Escape key
            glutHideWindow();
            glutSetWindow(winMenu);
            glutShowWindow();
            soundEngine->stopAllSounds();
            break;
    }
}

