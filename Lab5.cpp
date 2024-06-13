#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

const float PI = 3.14159265358979323846;
GLuint cylinderList;
bool drawWireframe = false;
float rotationAngleX = 0.0f;
float rotationAngleY = 0.0f;
float rotationAngleZ = 0.0f;

void drawCylinder(float radius, float height, int segments)
{
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; ++i)
    {
        float theta = (2.0f * PI * float(i)) / float(segments);
        float x = radius * cos(theta);
        float z = radius * sin(theta);

        // Draw the bottom point
        glVertex3f(x, -height / 2.0f, z);

        // Draw the top point
        glVertex3f(x, height / 2.0f, z);
    }
    glEnd();

    // Draw the top and bottom faces
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, height / 2.0f, 0.0f); // Center of the top face
    for (int i = 0; i <= segments; ++i)
    {
        float theta = (2.0f * PI * float(i)) / float(segments);
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glVertex3f(x, height / 2.0f, z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, -height / 2.0f, 0.0f); // Center of the bottom face
    for (int i = 0; i <= segments; ++i)
    {
        float theta = (2.0f * PI * float(i)) / float(segments);
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        glVertex3f(x, -height / 2.0f, z);
    }
    glEnd();
}

// the setup function
void createCylinderList(float radius, float height, int segments)
{
    cylinderList = glGenLists(1);
    glNewList(cylinderList, GL_COMPILE);

    drawCylinder(radius, height, segments);

    glEndList();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotationAngleZ, 0.0f, 0.0f, 1.0f);

    if (drawWireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPushMatrix();
    glTranslatef(0.0f, 0.7f, 0.0f);
    glColor3f(0.8, 0.65, 0.5);
    drawCylinder(0.8f, 0.1f, 50);
    glPopMatrix();

    // First leg
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.7f);
    glRotatef(-25.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.4, 0.2, 0.0);
    glCallList(cylinderList);
    glPopMatrix();

    // Second leg
    glPushMatrix();
    glTranslatef(0.6f, -0.04f, -0.5f);
    glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.4, 0.2, 0.0);
    glCallList(cylinderList);
    glPopMatrix();

    // Third leg
    glPushMatrix();
    glTranslatef(-0.6f, -0.04f, -0.5f);
    glRotatef(165.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(165.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.4, 0.2, 0.0);
    glCallList(cylinderList);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
        rotationAngleX += 5.0f;
        break;
    case 'X':
        rotationAngleX -= 5.0f;
        break;
    case 'y':
        rotationAngleY += 5.0f;
        break;
    case 'Y':
        rotationAngleY -= 5.0f;
        break;
    case 'z':
        rotationAngleZ += 5.0f;
        break;
    case 'Z':
        rotationAngleZ -= 5.0f;
        break;
    case ' ':
        drawWireframe = !drawWireframe;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void printUserActions()
{
    cout << "User Actions:" << endl;
    cout << "Press 'x' to rotate the object around the x-axis in the positive direction." << endl;
    cout << "Press 'X' to rotate the object around the x-axis in the negative direction." << endl;
    cout << "Press 'y' to rotate the object around the y-axis in the positive direction." << endl;
    cout << "Press 'Y' to rotate the object around the y-axis in the negative direction." << endl;
    cout << "Press 'z' to rotate the object around the z-axis in the positive direction." << endl;
    cout << "Press 'Z' to rotate the object around the z-axis in the negative direction." << endl;
    cout << "Press the space bar to toggle between wireframe and solid mode." << endl;
}

int main(int argc, char **argv)
{
    printUserActions();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Makario's 3-Legged Stool");
    glEnable(GL_DEPTH_TEST);
    createCylinderList(0.1f, 1.5f, 30); // Create the display list for the cylinder
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
