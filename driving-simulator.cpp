#include "library.h"
#include "Timer.cpp"
#include "Circuit.cpp"

#define MAXSPEED 40.0
#define COEFF 0.03
#define COEFF_TURN 1
#define PI (2*acos(0.0))
#define LAPS 3

float lx=0.0f,lz=-1.0f; // actual vector representing the camera's direction
double speed = 0.0;
time_t oldTime_fps;
Timer starting_timer;
Timer lapTimes[3];
int penalities[4];

Timer reduceNoiseCollision;
unsigned long time_recorded = 0;
int fps = 0;

float teta = .01;
bool enoughTime = true;
int numberOfLaps = 0;
int maxLaps = 3;

bool outOfTheRoad = false;
bool turn_left = false;
bool turn_right = false;
bool finished = false;
int vue_level = 0; //point of vue,  0 : default,    1 : first,    2 : far away
int vue_count = 3;
Circuit circuit;

// The different windows
int winMenu, winGuide, winRun, winTrackSelection;

bool first_display;

int trackSelected;

ISoundEngine* soundEngine; //for main sound

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
    glutKeyboardFunc(keyboardTrackSelection);
    glutHideWindow();

    // Main application
    glutInitWindowSize(WINDOW_W_H_RUN, WINDOW_W_H_RUN);
    winRun = glutCreateWindow("car driving test");
    glutDisplayFunc(display);
    glutReshapeFunc(stopReshapeMain);
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

    glEnable(GL_DEPTH_TEST);
    /*glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_CLAMP);*/

    glutMainLoop();

    /* End of programme */

    if(soundEngine) {
        soundEngine->drop(); // delete soundEngine
    }
    //glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

    return 0;
}

void turn();

void display() {
    if (!finished){
        if (first_display) {
            circuit.generate_circuit(trackSelected); //with track selected
            //circuit.print();
            first_display = false;
            starting_timer.start();
        }

        if (numberOfLaps > LAPS) { // 3 tour de circuit
            finished = true;

            // play final sound
            soundEngine->stopAllSounds();
            soundEngine->play2D("./irrKlang/media/final.ogg", true, false, true);
            if(soundEngine) {
                soundEngine->setSoundVolume(0.5f);
            }

            return;
        }

        // get FPS :
        ++fps;
        time_t temp = time(nullptr);
        auto diff_second = (unsigned long) difftime(temp, oldTime_fps);
        if (diff_second >= 1) {
            oldTime_fps = temp;
            //printf("FPS=%i\n", fps);
            fps = 0;
        }

        //cooldown timer for finished lap's detection
        if (starting_timer.elapsedSeconds() >= 8) {
            enoughTime = true;
        }

        if (circuit.isOnTheRoad()) {
            if (!reduceNoiseCollision.isRunning())
                reduceNoiseCollision.start();
            outOfTheRoad = false;
        } else {
            if (reduceNoiseCollision.elapsedMilliseconds() > 500 && reduceNoiseCollision.isRunning()) {
                outOfTheRoad = true;
                if (penalities[numberOfLaps] >= 0) {
                    penalities[numberOfLaps] += 10;
                } else {
                    penalities[numberOfLaps] = 10;
                }
                reduceNoiseCollision.stop();

            } else {
                reduceNoiseCollision.start();
            }
        }
    }
    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (outOfTheRoad) {
        glClearColor(1, 0.7, 0.7,0.7);	//color white/red
    } else {
        glClearColor(.7, 0.7, 1,0.7);	//color white/blue
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /********************
            camera setup
        ********************/

    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    if(finished){
        gluLookAt(0,100, 50,	0+lx,-990, 0+lz,	0,0,1);
        //gluLookAt(0,-100, 30,	0+lx,+990, 0+lz,	0,0,1);
        //gluLookAt(-100,-100, 20,	+990,+990, 0+lz,	0,0,1);
    } else {
        switch (vue_level) {
            case 0: // default vue
                gluLookAt(0,50, 10,	0+lx,-990, 0+lz,	0,0,1);
                break;
            case 1: // first
                gluLookAt(0,0, 10,	0+lx,-990, 0+lz,	0,0,1);
                break;
            case 2: // far
                gluLookAt(0,100, 30,	0+lx,-990, 0+lz,	0,0,1);
                break;
            default:
                std::cout << "Problem with vue" << std::endl;
        }
    }


    glMatrixMode(GL_MODELVIEW);
    teta *= 0.8;
    speed *= 0.995;

    if (teta > 0.001) {
        if (turn_right) {
            circuit.rotateCircuit(-teta);
            circuit.rotateCircuit(teta);
        } else if (turn_left) {
            circuit.rotateCircuit(teta);
            circuit.rotateCircuit(-teta);
        }
    }

    if (enoughTime) {
        if (circuit.isLapPassed()) {
            numberOfLaps++;
            enoughTime = false;

            if (numberOfLaps <= maxLaps+1 && numberOfLaps != 1) {
                starting_timer.stop();
                lapTimes[numberOfLaps-2] = starting_timer;
            }
            starting_timer.start();
        }
    }

    circuit.shiftCircuit(speed);
    drawPolygonsFromVectors(circuit.roads, -30.0, 0.245, 0.245, 0.245);
    drawPolygonsFromVectors(circuit.middle_roads, -29.80, 1, 1, 1);

    drawMainCar(0, 0);
    drawHUD(speed, numberOfLaps, maxLaps, lapTimes, penalities, outOfTheRoad);
    glutSwapBuffers();

}

void animate() {

    /*******************
         key listeners
      ******************/

    if (!finished){
        if (keys.IS_KEY_UP) {
            acceleration(speed);
        }
        if (keys.IS_KEY_DOWN) {
            speed = deceleration(speed);
        }
        if (keys.IS_KEY_LEFT) {
            turn();
            turn_right = false;
            turn_left = true;
            circuit.rotateCircuit(teta);
            circuit.rotateCircuit(-teta);
        }

        if (keys.IS_KEY_RIGHT) {
            turn();
            turn_right = true;
            turn_left = false;
            circuit.rotateCircuit(-teta);
            circuit.rotateCircuit(teta);
        }
    }    double ratio = 20/sqrt(2);

    glutPostRedisplay();
}

void turn() {
    if (speed < 1) {
        teta = 0;
        return;
    }
    if (speed < MAXSPEED/28) {
        teta = 0.006;
        return;
    }
    if (speed < (MAXSPEED/14)*2) {
        teta = 0.006;
        return;
    }
    if (speed < (MAXSPEED/14)*3) {
        teta = 0.006;
        return;
    }
    if (speed < (MAXSPEED/14)*4) {
        teta = 0.006;
        return;
    }
    if (speed < (MAXSPEED/14)*5) {
        teta = 0.005;
        return;
    }
    if (speed < (MAXSPEED/7)*3) {
        teta = 0.004;
        return;
    }
    if (speed < (MAXSPEED/7)*4) {
        teta = 0.003;
        return;
    }
    if (speed < (MAXSPEED/7)*5) {
        teta = 0.003;
        return;
    }
    if (speed < (MAXSPEED/7)*6) {
        teta = 0.003;
        return;
    }
    if (speed < MAXSPEED) {
        teta = 0.003;
        return;
    }
}

void init() {
    first_display = true;

    circuit.generate_circuit(trackSelected); //with track selected
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

void acceleration(double &speed_x) {
    if (speed_x == MAXSPEED) {
        //std::cout << 1 << std::endl;
        return;
    }
    if (speed_x < MAXSPEED/28) {
        if (speed < 1) {
            speed_x = 1;
        }
        speed_x += (speed_x * 0.5) * COEFF;
        return;
    }
    if (speed_x < (MAXSPEED/14)*2) {
        speed_x += (speed_x * 1.8) * COEFF;
        return;
    }
    if (speed_x < (MAXSPEED/14)*3) {
        //std::cout << 3 << std::endl;
        speed_x += (speed_x * 1.9) * COEFF;
        return;
    }
    if (speed_x < (MAXSPEED/14)*4) {
        //std::cout << 3 << std::endl;
        speed_x += (speed_x * 2.3) * COEFF;
        return;
    }
    if (speed_x < (MAXSPEED/14)*5) {
        //std::cout << 3 << std::endl;
        speed_x += (speed_x * 2) * COEFF;
        return;
    }
    if (speed_x < (MAXSPEED/7)*3) {
        //std::cout << 4 << std::endl;
        speed_x += (speed_x * 1.3) * COEFF;
        return;
    }
    if (speed_x < (MAXSPEED/7)*4) {
        //std::cout << 5 << std::endl;
        speed_x += (speed_x * 0.7) * COEFF;
        return;
    }
    if (speed_x < (MAXSPEED/7)*5) {
        //std::cout << 6 << std::endl;
        speed_x += (speed_x * 0.5) * COEFF;
        return;
    }
    if (speed_x < (MAXSPEED/7)*6) {
        //std::cout << 7 << std::endl;
        speed_x += (speed_x * 0.25) * COEFF;
        return;
    }
    if (speed_x < MAXSPEED) {
        //std::cout << 8 << std::endl;
        speed_x += (speed_x * 0.19) * COEFF;
        return;
    }
    //std::cout << 9 << std::endl;
    speed_x = MAXSPEED;
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
        case 27: // Escape key -> go back to the menu
            glutHideWindow();
            glutSetWindow(winMenu);
            glutShowWindow();
            soundEngine->setAllSoundsPaused();
            break;
        case 9: // Tabulation key -> change view
            vue_level = (vue_level + 1) % vue_count;
            break;
    }
}

