// Generating ELLIPSE primitives (Using Mid point approach, Bresenham’s Approach)

#include <stdio.h>
#include <GLUT/glut.h>

void drawSymmetricalPoints(int x, int y) {
    glVertex2i(x, y);
    glVertex2i(-x, y);
    glVertex2i(x, -y);
    glVertex2i(-x, -y);
}

void bresenham(int a, int b) {
    glColor3f(1.0, 0.0, 0.0);
    
    int x = 0, y = b;
    float dk = 1 - 2*b + 2.0*b*b/(a*a);
    drawSymmetricalPoints(x, y);

    while (x * b * b <= y * a * a) {
        if (dk > 0) {
            dk = dk - 4*(y-1) + 2.0*b*b*(2*x+3)/(a*a);
            y = y - 1;
        } else {
            dk = dk + 2.0*b*b*(2*x+3)/(a*a);
        }
        x = x + 1;
        drawSymmetricalPoints(x, y);
    }

    x = a; y = 0;
    dk = 1 - 2*a + 2.0*a*a/(b*b);
    drawSymmetricalPoints(x, y);

    while (x * b * b > y * a * a) {
        if (dk > 0) {
            dk = dk - 4*(x-1) + 2.0*a*a*(2*y+3)/(b*b);
            x = x - 1;
        } else {
            dk = dk + 2.0*a*a*(2*y+3)/(b*b);
        }
        y = y + 1;
        drawSymmetricalPoints(x, y);
    }
}

void midpoint(int a, int b) {
    glColor3f(0.0, 1.0, 0.0);

    int x = 0, y = b;
    float dk = b * b - a * a * b + a * a / 4.0;
    drawSymmetricalPoints(x, y);

    while (x * b * b <= y * a * a) {
        if (dk > 0) {
            dk = dk + b * b * (2 * x + 3) + 2 * a * a * (1 - y);
            y = y - 1;
        } else {
            dk = dk + b * b * (2 * x + 3);
        }
        x = x + 1;
        drawSymmetricalPoints(x, y);
    }

    dk = a * b * b + b * b / 4.0 + a * a;
    while (y > 0) {
        if (dk > 0) {
            dk = dk + a * a * (3 - 2 * y);
        } else {
            dk = dk + a * a * (3 - 2 * y) + 2 * b * b * (x + 1);
            x = x + 1;
        }
        y = y - 1;
        drawSymmetricalPoints(x, y);
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    
    bresenham(170, 70);
    midpoint(200, 100);

    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Ellipse Primitives");
    glLoadIdentity();
    gluOrtho2D(-250,250,-250,250);
    glutDisplayFunc(display);
    glutMainLoop();
}