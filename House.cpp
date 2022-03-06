#include "House.h"

class House : Decor {
    void print() override{
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
    }
};