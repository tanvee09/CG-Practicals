// Implement LINE CLIPPING approach using COHEN SUTHERLAND

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

void swap(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
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

unsigned char encode (int x, int y) {
    unsigned char code = 0x00;
    if (x < xwmin) code |= LEFT_EDGE;
    if (x > xwmax) code |= RIGHT_EDGE;
    if (y < ywmin) code |= BOTTOM_EDGE;
    if (y > ywmax) code |= TOP_EDGE;
    return code;
}

void clipLine(float x1, float y1, float x2, float y2) {
    unsigned char code1, code2;
    int done = 0, draw = 0;

    while (!done) {
        code1 = encode(x1, y1);
        code2 = encode(x2, y2);

        if (ACCEPT(code1, code2)) {
            done = draw = 1;
        } else if (REJECT(code1, code2)) {
            done = 1;
        } else {
            if (INSIDE(code1)) {
                swap(&x1, &x2);
                swap(&y1, &y2);
                char t = code1;
                code1 = code2;
                code2 = t;
            }
            float m = 0;
            if (x1 != x2) {
                m = (y2 - y1) * 1.0 / (x2 - x1);
            }

            if (code1 & LEFT_EDGE) {
                y1 += (xwmin - x1) * m;
                x1 = xwmin;
            } else if (code1 & RIGHT_EDGE) {
                y1 += (xwmax - x1) * m;
                x1 = xwmax;
            } else if (code1 & BOTTOM_EDGE) {
                if (x1 != x2) 
                    x1 += (ywmin - y1) / m;
                y1 = ywmin;
            } else if (code1 & TOP_EDGE) {
                if (x1 != x2) 
                    x1 += (ywmax - y1) / m;
                y1 = ywmax;
            }
        }
    }

    if (draw) {
        point(x1, y1);
        point(x2, y2);
    }
}

void display(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    clippingWindow();
    line(200, 200, 450, 250);
    clipLine(200, 200, 450, 250);
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cohen Sutherland Line Clipping");
    gluOrtho2D(0,500,0,500);
    glutDisplayFunc(display);
    glutMainLoop();
}