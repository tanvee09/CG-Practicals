// Implement POLYGON CLIPPING approach using SUTHERLAND HODGMAN

#include <stdio.h>
#include <GLUT/glut.h>

typedef enum {Left, Right, Bottom, Top} Edge;
const int N_EDGE = 4;

int xwmin = 100, xwmax = 400, ywmin = 100, ywmax = 300;

struct point {
    float x, y;
};

void drawPolygon(struct point *pIn, int n) {
    glColor3f(1.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(pIn[i].x, pIn[i].y);
    }
    glEnd();
}

void drawClippedPolygon(struct point *pIn, int n) {
    glColor3f(0.0, 1.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glLineWidth(3.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        glVertex2f(pIn[i].x, pIn[i].y);
    }
    glEnd();
}

int inside(struct point p, Edge b) {
    switch(b) {
        case Left:   if (p.x < xwmin) return 0; break;
        case Right:  if (p.x > xwmax) return 0; break;
        case Bottom: if (p.y < ywmin) return 0; break;
        case Top:    if (p.y > ywmax) return 0; break;
    }
    return 1;
}

int cross(struct point p1, struct point p2, Edge b) {
    return inside(p1, b) != inside(p2, b);
}

struct point intersect(struct point p1, struct point p2, Edge b) {
    struct point ipt;
    float m;
    if (p1.x != p2.x) m = (p2.y - p1.y) / (p2.x - p1.x);
    
    switch(b) {
        case Left:
            ipt.x = xwmin;
            ipt.y = p2.y + (xwmin - p2.x) * m;
            break;
        case Right: 
            ipt.x = xwmax;
            ipt.y = p2.y + (xwmax - p2.x) * m;
            break;
        case Bottom:
            ipt.y = ywmin;
            if (p1.x != p2.x) ipt.x = p2.x + (ywmin - p2.y) / m;
            else ipt.x = p2.x;
            break;
        case Top:
            ipt.y = ywmax;
            if (p1.x != p2.x) ipt.x = p2.x + (p2.y - ywmax) / m;
            else ipt.x = p2.x;
            break;
    }
    return ipt;
}

void clipPoint(struct point p, Edge b, struct point *pOut, int *count, struct point* first, struct point *s) {
    if (first[b].x == -1) {
        first[b] = p;
    } else if (cross(p, s[b], b)) {
        struct point ipt = intersect(p, s[b], b);
        if (b < Top) {
            clipPoint(ipt, b + 1, pOut, count, first, s);
        } else {
            pOut[*count] = ipt;
            (*count)++;
        }
    }

    s[b] = p;
    
    if (inside(p, b)) {
        if (b < Top) {
            clipPoint(p, b + 1, pOut, count, first, s);
        } else {
            pOut[*count] = p;
            (*count)++;
        }
    }
}

void closeClip(struct point *pOut, int *count, struct point* first, struct point *s) {
    for (Edge b = Left; b <= Top; b++) {
        if (cross(s[b], first[b], b)) {
            struct point ipt = intersect(s[b], first[b], b);
            if (b < Top) {
                clipPoint(ipt, b + 1, pOut, count, first, s);
            } else {
                pOut[*count] = ipt;
                (*count)++;
            }
        }
    }
}

int clipPolygon(int n, struct point *pIn, struct point *pOut) {
    struct point first[N_EDGE] = {{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}};
    struct point s[N_EDGE];
    int count = 0;
    for (int i = 0; i < n; i++) {
        clipPoint(pIn[i], Left, pOut, &count, first, s);
    }
    closeClip(pOut, &count, first, s);
    return count;
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

void display() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    struct point pIn[3] = {{150,50}, {30,150}, {300,250}};
    struct point pOut[10];
    drawPolygon(pIn, 3);
    clippingWindow();
    int count = clipPolygon(3, pIn, pOut);
    drawClippedPolygon(pOut, count);
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Sutherland Hodgman Polygon Clipping");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}