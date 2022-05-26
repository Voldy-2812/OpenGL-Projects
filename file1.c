#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#define FL GLfloat
#define FLd GLdouble

FL X, Y, Z, radius = 1.5;

void display() {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -10.0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);

    glColor3f(0.0, 0.0, 1.0);
    glutSolidSphere(radius, 50, 50);

    glPopMatrix();
    glPushMatrix();

    glRotatef(Y, 0.0, 1.0, 0.0);
    glTranslatef(5.0, 0.0, 0.0);

    glColor3f(1.0,1.0,1.0);
    glutSolidSphere(radius/6, 50, 50);

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void idleFunc(){
    if(Z > 360.0) {
        Z -= 360.0*floor(Z/360.0);
    }
    if(Y > 360.0) {
        Y -= 360.0*floor(Y/360.0);
    }
    Z += 0.04;
    Y += 0.04;
    display();
}

void Init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(int x, int y) {
    if(x == 0 || y == 0) {
        return;
    }
    glMatrixMode(GL_PROJECTION);

    gluPerspective(40.0, (FLd)x/(FLd)y, 0.6, 40.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 10);
    glutInitWindowSize(900, 600);
    glutCreateWindow("MOON revolving around EARTH");
    Init();

    glutIdleFunc(idleFunc);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
