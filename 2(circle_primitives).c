// Generating CIRCLE primitives (Using Mid point approach, Bresenham’s Approach)

#include <stdio.h>
#include <GLUT/glut.h>

void drawSymmetricalPoints(int x, int y) {
    glVertex2i(x, y);
    glVertex2i(-x, y);
    glVertex2i(x, -y);
    glVertex2i(-x, -y);
    glVertex2i(y, x);
    glVertex2i(-y, x);
    glVertex2i(y, -x);
    glVertex2i(-y, -x);
}

void bresenham(int r) {
    glColor3f(1.0, 0.0, 0.0);
    
    int x = 0, y = r;
    int dk = 3 - 2 * r;
    drawSymmetricalPoints(x, y);

    while (x < y) {
        if (dk > 0) {
            dk = dk + 4 * (x - y) + 10;
            y = y - 1;
        } else {
            dk = dk + 4 * x + 6;
        }
        x = x + 1;
        drawSymmetricalPoints(x, y);
    }
}

void midpoint(int r) {
    glColor3f(0.0, 1.0, 0.0);

    int x = 0, y = r;
    float dk = 5.0/4 - r;
    drawSymmetricalPoints(x, y);

    while (x < y) {
        if (dk > 0) {
            dk = dk + 5 + 2 * (x - y);
            y = y - 1;
        } else {
            dk = dk + 3 + 2 * x;
        }
        x = x + 1;
        drawSymmetricalPoints(x, y);
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    
    bresenham(100);
    midpoint(150);

    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Circle Primitives");
    glLoadIdentity();
    gluOrtho2D(-250,250,-250,250);
    glutDisplayFunc(display);
    glutMainLoop();
}