#include "library.h"
#include "Timer.cpp"
#include "Circuit.cpp"

#define MAXSPEED 200.0
#define COEFF 1
#define COEFF_TURN 1
#define PI (2*acos(0.0))


float lx=0.0f,lz=-1.0f; // actual vector representing the camera's direction
double leftRightMove = 0;
double sky = -1000;
double speed = 0.0;
time_t oldTime_fps;
time_t oldTime_enough;
time_t starting_time = time(nullptr);
Timer starting_timer;
Timer lapTimes[3];

Timer reduceNoiseCollision;
unsigned long time_recorded = 0;
int fps = 0;
unsigned int state = 0; // different than 0 for shake camera

float turn = .01;
bool enoughTime = true;
int numberOfLaps = 0;
int maxLaps = 3;
bool outOfTheRoad = false;

Circuit circuit;

// The different windows
int winMenu, winGuide, winRun, winTrackSelection;

int trackSelected;

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

    // Window and callback functions for Track Selection
    winTrackSelection = glutCreateWindow("Track Selection");
    glutDisplayFunc(renderTrackSelection);
    glutReshapeFunc(stopReshape);
    glutMouseFunc(mouseTrackSelection);
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
bool first_display = true;
void display() {
    if (first_display) {
        circuit.generate_circuit(trackSelected); //with track selected
        circuit.print();
        first_display = false;
        starting_timer.start();
    }

    if (numberOfLaps > maxLaps) { // 3 tour de circuit
        return;
    }

    // get FPS :
    ++fps;
    time_t temp = time(nullptr);
    auto diff_second = (unsigned long) difftime(temp, oldTime_fps);
    if(diff_second >= 1){
        oldTime_fps = temp;
        //printf("FPS=%i\n", fps);
        fps = 0;
    }

    //cooldown timer for finished lap's detection
    diff_second = (unsigned long) difftime(temp, oldTime_enough);
    if (diff_second >= 15) {
        oldTime_enough = temp;
        enoughTime = true;
    }



    if (circuit.isOnTheRoad()) {
        if (!reduceNoiseCollision.isRunning())
            reduceNoiseCollision.start();
        outOfTheRoad = false;
        std::cout << "on the road" << std::endl;
    } else {
        if (reduceNoiseCollision.elapsedMilliseconds() > 500 && reduceNoiseCollision.isRunning()) {
            std::cout << "OUT OF THE ROAD " << std::endl;
            outOfTheRoad = true;
            reduceNoiseCollision.stop();
        } else {
            reduceNoiseCollision.start();
        }
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

    gluLookAt(0,50, 10,	0+lx,-99999999999, 0+lz,	0,0,1);
    /*
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
     */

    glMatrixMode(GL_MODELVIEW);
    speed *= 0.98;

    if (enoughTime) {
        if (circuit.isLapPassed()) {

            numberOfLaps++;
            std::cout << "number of lap(s) : " << numberOfLaps << "\n";
            enoughTime = false;

            if (numberOfLaps <= maxLaps+1 && numberOfLaps != 1) {
                starting_timer.stop();
                lapTimes[numberOfLaps-2] = starting_timer;
                std::cout << lapTimes[numberOfLaps-2].elapsedMilliseconds() << "\n";
                starting_timer.start();
                starting_time = time(nullptr);
            }
        }
    }

    circuit.shiftCircuit(speed);
    drawPolygonsFromVectors(circuit.roads, -30.0, 0.245, 0.245, 0.245);
    drawPolygonsFromVectors(circuit.middle_roads, -29.80, 1, 1, 1);

    drawMainCar(leftRightMove, 0);
    /*
    drawBackground(sky);
    drawHill(sky);
    */
    drawHUD(speed, numberOfLaps, maxLaps, lapTimes);
    glutSwapBuffers();

}

void animate() {

    /*******************
         key listeners
      ******************/

    if(keys.IS_KEY_UP) {
        acceleration(speed);
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

void acceleration (double &speed_x) {
    if (speed_x == MAXSPEED)
        return;
    if (speed_x < MAXSPEED/(MAXSPEED/7.4)) {
        speed_x += 0.05 * COEFF;
    }
    if (speed_x < MAXSPEED/(MAXSPEED/6.6666)) {
        speed_x += 0.5*COEFF;
    } else if (speed_x < (MAXSPEED/3.3333)) {
        speed_x += 0.3*COEFF;
    } else if (speed_x < (MAXSPEED/1.428)) {
        speed_x += 0.2*COEFF;
    } else if (speed_x < (MAXSPEED/1.2)) {
        speed_x += 0.1*COEFF;
    } else {
        speed_x + 0.07*COEFF;
        if (speed_x > MAXSPEED)
            speed_x = MAXSPEED;
    }
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

