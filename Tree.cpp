#include "Tree.h"

class Tree : Deco {
    void print() override {
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
};