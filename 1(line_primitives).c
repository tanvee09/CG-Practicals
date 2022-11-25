// Generating Line primitives (Using DDA, Mid point approach, Bresenham’s Approach)

#include <stdio.h>
#include <GLUT/glut.h>
#include <math.h>

void dda(int x0, int y0, int x1, int y1) {
    glColor3f(1.0, 0.0, 0.0);

    int dx = x1 - x0, 
        dy = y1 - y0;
    float steps = dx > dy ? dx : dy;
    float xinc = dx / steps, 
          yinc = dy / steps;

    float x = x0, y = y0;
    glVertex2i(x, y);

    for (int i = 0; i < steps; i++) {
        x += xinc;
        y += yinc;
        glVertex2i(round(x), round(y));
    }
}

void bresenham(int x0, int y0, int x1, int y1) {
    glColor3f(0.0, 1.0, 0.0);
    
    int dx = x1 - x0, dy = y1 - y0;
    int cdx = x1 * y0 - x0 * y1;

    int x = x0, y = y0;
    int dk = 2 * dx * y - 2 * dy * (x + 1) - 2 * cdx + dx;
    glVertex2i(x, y);

    while (x != x1) {
        if (dk > 0) {
            dk = dk - 2 * dy;
        } else {
            dk = dk + 2 * (dx - dy);
            y = y + 1;
        }
        x = x + 1;
        glVertex2i(x, y);
    }
}

void midpoint(int x0, int y0, int x1, int y1) {
    glColor3f(0.0, 0.0, 1.0);

    float m = (y1 - y0) * 1.0 / (x1 - x0),
          c = (x1 * y0 - x0 * y1) * 1.0 / (x1 - x0);

    int x = x0, y = y0;
    float dk = m * (x + 1) + c - (y + 1.0/2);
    glVertex2i(x, y);

    while (x != x1) {
        if (dk > 0) {
            y = y + 1;
            dk = dk + m - 1;
        } else {
            dk = dk + m;
        }
        x = x + 1;
        glVertex2i(x, y);
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    
    dda(10, 10, 400, 100);
    bresenham(10, 10, 400, 200);
    midpoint(10, 10, 400, 300);

    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Line Primitives");
    gluOrtho2D(0,500,0,500);
    glutDisplayFunc(display);
    glutMainLoop();
}