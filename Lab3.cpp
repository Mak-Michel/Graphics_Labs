#include <iostream>
#include <ctime>

#include <GL/glew.h>
#include <GL/freeglut.h>

#define _USE_MATH_DEFINES
#include <cmath>

static const int MAX_VERTICES = 1000;

// Structure to represent a vertex
struct Vertex
{
    float x, y, z;
};

// Function to generate a random color
void setRandomColor()
{
    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
}

// Function to draw a helix
void drawHelix(float Xc, float Yc, float R, float P, int numVertices)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < numVertices; ++i)
    {
        float t = 5.0 * M_PI * i / MAX_VERTICES;
        float x = Xc + R * cos(t);
        float y = Yc + R * sin(t);
        float z = P * t;
        setRandomColor();
        glVertex3f(x, y, z);
    }
    glEnd();
}

// Function to draw a sphere
void drawSphere(int slices, int stacks, bool wireframe)
{
    if (wireframe)
        glutWireSphere(1.0, slices, stacks);
    else
        glutSolidSphere(1.0, slices, stacks);
}

// Globals.
static float helix_Xc = 0.0, helix_Yc = 0.0; // Center of the helix.
static float helix_R = 1.0;                  // Radius of the helix.
static float helix_P = 0.2;                  // Pitch of the helix.
static int helix_numVertices = 100;          // Number of vertices used to draw the helix.

static int sphere_slices = 16;        // Number of latitudinal slices for the sphere.
static int sphere_stacks = 16;        // Number of longitudinal slices for the sphere.
static bool sphere_wireframe = false; // Flag to draw sphere in wireframe mode or filled mode.

// //
int userChoice = 0;
// //

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw selected shape
    switch (userChoice)
    {
    case 1:
        drawHelix(helix_Xc, helix_Yc, helix_R, helix_P, helix_numVertices);
        break;
    case 2:
        drawSphere(sphere_slices, sphere_stacks, sphere_wireframe);
        break;
    }
    glFlush();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float fov = 60.0f; // Field of view angle
    float aspectRatio = (float)w / (float)h;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    // Calculate frustum based on perspective parameters
    float bottom = -tan(fov * 0.5f) * nearPlane;
    float top = tan(fov * 0.5f) * nearPlane;
    float left = bottom * aspectRatio;
    float right = top * aspectRatio;

    // Set up projection matrix
    glFrustum(left, right, bottom, top, nearPlane, farPlane);

    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'R':
        helix_R += 0.1;
        glutPostRedisplay();
        break;
    case 'r':
        helix_R -= 0.1;
        glutPostRedisplay();
        break;
    case 'H':
        helix_P += 0.1;
        glutPostRedisplay();
        break;
    case 'h':
        helix_P -= 0.1;
        glutPostRedisplay();
        break;
    case 'N':
        helix_numVertices += 10;
        glutPostRedisplay();
        break;
    case 'n':
        if (helix_numVertices > 10)
            helix_numVertices -= 10;
        glutPostRedisplay();
        break;
    case 'P':
        sphere_slices += 1;
        glutPostRedisplay();
        break;
    case 'p':
        if (sphere_slices > 3)
            sphere_slices -= 1;
        glutPostRedisplay();
        break;
    case 'Q':
        sphere_stacks += 1;
        glutPostRedisplay();
        break;
    case 'q':
        if (sphere_stacks > 3)
            sphere_stacks -= 1;
        glutPostRedisplay();
        break;
    case 'W':
    case 'w':
        sphere_wireframe = !sphere_wireframe;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(int userChoice)
{   
	switch (userChoice) {
            case 1:
                std::cout << "Interaction:" << std::endl;
                std::cout << "In case of helix:" << std::endl;
                std::cout << "Press R/r to increase/decrease radius of the helix." << std::endl
                          << "Press H/h to increase/decrease pitch of helix." << std::endl
                          << "Press N/n to increase/decrease number of vertices used to draw the helix." << std::endl;
                break;
            case 2:
                std::cout << "Interaction:" << std::endl;
                std::cout << "In case of sphere:" << std::endl;
                std::cout << "Press P/p to increase/decrease number of latitudinal slices." << std::endl
                          << "Press Q/q to increase/decrease number of longitudinal slices." << std::endl
                          << "Press W/w to toggle between wireframe and filled sphere." << std::endl;
                break;
    }
}

// Main routine.
int main(int argc, char **argv)
{
    srand(time(NULL)); // Seed random number generator

    std::cout << "Which shape do you want\n1) Helix\n2) Sphere\n>> \nEnter 1 or 2: ";
    std::cin >> userChoice;
    printInteraction(userChoice);
    
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Project");

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glEnable(GL_DEPTH_TEST);

    glewExperimental = GL_TRUE;
    glewInit();

    glutMainLoop();
    return 0;
}
