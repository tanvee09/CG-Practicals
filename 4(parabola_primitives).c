// Generating PARABOLA primitives (Using Mid point approach, Bresenham’s Approach)

#include <stdio.h>
#include <GLUT/glut.h>

void drawSymmetricalPoints(int x, int y) {
    glVertex2i(x, y);
    glVertex2i(x, -y);
}

void bresenham(int a) {
    glColor3f(1.0, 0.0, 0.0);
    
    int x = 0, y = 0;
    int dk = 2 * a - 1;
    drawSymmetricalPoints(x, y);

    while (x < a) {
        if (dk > 0) {
            dk = dk - 2 * y - 3;
        } else {
            dk = dk - 2 * y + 4 * a - 3;
            x = x + 1;
        }
        y = y + 1;
        drawSymmetricalPoints(x, y);
    }

    x = a;
    y = 2 * a;
    dk = 4 * a + 1;
    drawSymmetricalPoints(x, y);

    while (x < 200) {
        if (dk > 0) {
            dk = dk - 8 * a;
        } else {
            dk = dk + 4 * (y + 1) - 8 * a;
            y = y + 1;
        }
        x = x + 1;
        drawSymmetricalPoints(x, y);
    }
}

void midpoint(int a) {
    glColor3f(0.0, 1.0, 0.0);

    int x = 0, y = 0;
    float dk = 1 - 2 * a;
    drawSymmetricalPoints(x, y);

    while (x < a) {
        if (dk > 0) {
            dk = dk + 2 * y + 3 - 4 * a;
            x = x + 1;
        } else {
            dk = dk + 2 * y + 3;
        }
        y = y + 1;
        drawSymmetricalPoints(x, y);
    }

    x = a;
    y = 2 * a;
    dk = 1.0/4 - 2 * a;
    drawSymmetricalPoints(x, y);

    while (x < 200) {
        if (dk < 0) {
            dk = dk + 2 * y + 2 - 4 * a;
            y = y + 1;
        } else {
            dk = dk - 4 * a;
        }
        x = x + 1;
        drawSymmetricalPoints(x, y);
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    
    bresenham(30);
    midpoint(40);

    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Parabola Primitives");
    glLoadIdentity();
    gluOrtho2D(-250,250,-250,250);
    glutDisplayFunc(display);
    glutMainLoop();
}