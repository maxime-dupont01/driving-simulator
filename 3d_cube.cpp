#include <GL/glut.h>

int object = 0;
float xmove[]{ 0, 0 };
float ymove[]{ 0, 0 };
float zmove[]{ 0, 0 };

void keyboard(int button, int x, int y)
{
    switch (button)
    {
        case GLUT_KEY_F1: object = 0; break;
        case GLUT_KEY_F2: object = 1; break;
        case GLUT_KEY_LEFT: xmove[object] -= 0.1; break;
        case GLUT_KEY_RIGHT: xmove[object] += 0.1; break;
        case GLUT_KEY_DOWN:  ymove[object] -= 0.1; break;
        case GLUT_KEY_UP: ymove[object] += 0.1; break;
        case GLUT_KEY_PAGE_UP: zmove[object] -= 0.1; break;
        case GLUT_KEY_PAGE_DOWN: zmove[object] += 0.1; break;
    }
    glutPostRedisplay();
}

void Settings()
{
    glClearColor(1,1,1,0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST);
}

void polygons(void)
{

    glPushMatrix();

    glTranslatef(-1.5, 0.0, -8.0);
    glTranslatef(xmove[1], ymove[1], zmove[1]); // <--- translate cube


    glBegin(GL_QUADS); //cubic
    glColor3f(1.0f, 0.0f, 1.0f); //pink
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    //down face
    glColor3f(1.0f, 0.5f, 0.0f); //orange
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    //front face
    glColor3f(0.0f, 0.0f, 1.0f); //blue
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    //back
    glColor3f(1.0f, 1.0f, 0.0f); //yellow
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    //left
    glColor3f(1.0f, 0.0f, 0.0f); //red
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    //right
    glColor3f(0.0f, 1.0f, 0.0f); //green
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();

    glPopMatrix();
}

void DrawingFunction()//painting
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    polygons();
    glutSwapBuffers();
}

void AppearanceAdjustment(int x, int y)
{
    int aspect = x / y;
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,aspect,0.1,20);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3d shapes");
    glutDisplayFunc(DrawingFunction);
    glutReshapeFunc(AppearanceAdjustment);
    glutSpecialFunc(keyboard);
    Settings();
    glutMainLoop();
    return 0;
}