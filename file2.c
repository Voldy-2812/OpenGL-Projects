#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#define FL GLfloat
#define FLd GLdouble

FL X, Y, Z, radius = 1.5;
FL qaBlack[] = {0.0, 0.0, 0.0, 1.0};
FL qaBlue[] = {0.0, 0.0, 1.0, 1.0};
FL qaWhite[] = {1.0, 1.0, 1.0, 1.0};
FL qaRed[] = {1.0, 0.0, 0.0, 1.0};

FL qaAmbientLight[] = {0.1, 0.1, 0.1, 1.0};
FL qaDiffuseLight[] = {1.0, 1.0, 1.0, 1.0};
FL qaSpecularLight[] = {0.0, 0.0, 0.0, 1.0};
FL emitLight[] = {0.9, 0.9, 0.9, 0.01};
FL noEmit[] = {0.0, 0.0, 0.0, 1.0};
FL qaLightPositon[] = {0.0, 0.0, 0.0, 1.0};

void display() {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaBlue);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaBlue);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.2);
    glutSolidSphere(radius, 50, 50);

    glPopMatrix();
    glPushMatrix();

    glRotatef(Y, 0.0, 1.0, 0.0);
    glTranslatef(5.0, 0.0, 0.0);

    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPositon);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLight);
    glutSolidSphere(radius/6, 50, 50);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, noEmit);

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

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
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
    initLighting();

    glutIdleFunc(idleFunc);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}

