// Implement LINE CLIPPING approach using LIANG BARSKY / CYRUS BECK

#include <stdio.h>
#include <GLUT/glut.h>

#define LEFT_EDGE   0x1
#define RIGHT_EDGE  0x2
#define BOTTOM_EDGE 0x4
#define TOP_EDGE    0x8

#define INSIDE(a)   (!a)
#define REJECT(a,b) (a&b)
#define ACCEPT(a,b) (!(a|b))

int xwmin = 100, xwmax = 400, ywmin = 100, ywmax = 300;

int clipTest(float p, float q, float *u1, float*u2) {
    if (p == 0) {
        if (q < 0) return 0;
    } else if (p < 0) {
        float r = q / p;
        if (r > *u2) return 0;
        else if (r > *u1) *u1 = r;
    } else {
        float r = q / p;
        if (r < *u1) return 0;
        else if (r < *u2) *u2 = r;
    }
    return 1;
}

void line(float x1, float y1, float x2, float y2) {
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

void point(float x, float y) {
    glColor3f(0.0, 1.0, 0.0);
    glPointSize(7.0);
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
}

void clippingWindow() {
    glColor3f(1.0, 1.0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_POLYGON);
    glVertex2i(xwmin, ywmin);
    glVertex2i(xwmin, ywmax);
    glVertex2i(xwmax, ywmax);
    glVertex2i(xwmax, ywmin);
    glEnd();
}

void clipLine(float x1, float y1, float x2, float y2) {
    float u1 = 0.0, u2 = 1.0, dx = x2 - x1, dy = y2 - y1;
    if (
        clipTest(-dx, x1 - xwmin, &u1, &u2) &&
        clipTest( dx, xwmax - x1, &u1, &u2) &&
        clipTest(-dy, y1 - ywmin, &u1, &u2) &&
        clipTest( dy, ywmax - y1, &u1, &u2)
    )  {
        if (u2 < 1) {
            x2 = x1 + u2 * dx;
            y2 = y1 + u2 * dy;
        }
        if (u1 > 0) {
            x1 += u1 * dx;
            y1 += u1 * dy;
        }
        point(x1, y1);
        point(x2, y2);
    }
}

void display(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    clippingWindow();
    line(200, 120, 450, 250);
    clipLine(200, 120, 450, 250);
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cyrus Beck Line Clipping");
    gluOrtho2D(0,500,0,500);
    glutDisplayFunc(display);
    glutMainLoop();
}