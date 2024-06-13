// Interaction:
// Press +/- to add/erase random point ---> good practice to add interaction as a comment at the top of source code

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <random>
#include <iostream>

using namespace std;

typedef struct
{
    float x;
    float y;
} Point;

vector<Point> points;

// window dimension
float windowWidth = 100.0;
float windowHeight = 100.0;

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0); // version 2 modification
    glLineWidth(1.0);   // Default line width

    /*
    ----------set point size below---------
    */
    glPointSize(5.0); // Set point size to 5.0
    //-------------------------------------

    /*
    ----------write points drawing logic below------------
    */
    glBegin(GL_POINTS);
    for (auto &point : points)
    {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    //----------------------------------------------------
    /*
    ----------write lines drawing logic below------------
    */
    glBegin(GL_LINES);
    for(int i = 0; i < points.size(); i+=2)
    {
        glVertex2f(points[i].x, points[i].y);
        if((i+1) < points.size()){
            glVertex2f(points[i+1].x, points[i+1].y);
        }
    }
    glEnd();
    //----------------------------------------------------
    glFlush();
}
// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}
// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    /*
    ------------- Add +/- cases handling below (handle corner cases)----------------
    */
    case 43:
        Point p;
        p.x = (rand() % (int)windowWidth);
        p.y = (rand() % (int)windowHeight);
        points.push_back(p);
        glutPostRedisplay();
        break;
    case 45:
        if (points.size() > 0)
        {
            points.pop_back();
            glutPostRedisplay();
        }
        break;
    //-----------------------------------------------------------------------
    default:
        break;
    }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Press +/- to add/erase random point" << endl;
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    printInteraction(); // good practice to print how to interact
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("RandomLines.cpp");
    glutDisplayFunc(drawScene); // drawing function
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput); // handle keyboard events

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}