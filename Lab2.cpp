/* write user interaction here for good practice */

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

enum choice
{
    ortho = 1,
    prespective = 2
};
enum userInput
{
    zoomIn = 'i',
    zoomOut = 'o',
    stopSpinning = ' ',
    CCW = GLUT_LEFT_BUTTON,
    CW = GLUT_RIGHT_BUTTON
};
int userChoice = 0;
float orthoLeft = -50;
float orthoRight = 50;
float orthoBottom = -50;
float orthoTop = 50;
float orthoNear = -5;
float orthoFar = 5;
float fruLeft = -5;
float fruRight = 5;
float fruBottom = -5;
float fruTop = 5;
float fruNear = 5;
float fruFar = 100;
float offsetX = 100;
float offsetY = 100;
float zOffset = -15; // zoom out/in
float windowWidth = 500;
float windowHeight = 500;
float spinY = 0;
float spinZ = 0;
float spinSpeed = 1000;
float currentSpin = 0;
float prevTime = 0;
bool spinning = false;

void drawTriangle()
{
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 10.0, 0.0);
    glVertex3f(-30.0, 0.0, 0.0);
    glVertex3f(30.0, 0.0, 0.0);
    glEnd();
}

void drawPyramid()
{
    glBegin(GL_TRIANGLES);
    // Base
    glVertex3f(5.0, 0.0, 5.0);
    glVertex3f(-5.0, 0.0, 5.0);
    glVertex3f(-5.0, 0.0, -5.0);
    glVertex3f(5.0, 0.0, 5.0);
    glVertex3f(5.0, 0.0, -5.0);
    glVertex3f(-5.0, 0.0, -5.0);
    // Sides
    glVertex3f(0.0, 5.0, 0.0);
    glVertex3f(5.0, 0.0, 5.0);
    glVertex3f(5.0, 0.0, -5.0);
    glVertex3f(0.0, 5.0, 0.0);
    glVertex3f(-5.0, 0.0, -5.0);
    glVertex3f(-5.0, 0.0, 5.0);
    glEnd();
}

void stopSpinningDisplay()
{
    spinning = false;
    glutIdleFunc(NULL);
}

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1.0); // Default line width.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    switch (userChoice)
    {
    case ortho:
        /*
            write code below:
            1- handle spinning hint: glRotatef
            2- draw triangle within viewing box
            Recommended points:
            (0, 10, 0)
            (-30, 0, 0)
            (30, 0, 0)
            you are encourged to change points location and observe its effects on rotation
        */
        // code here
        spinZ = currentSpin; // Update spin angle
        glRotatef(spinZ, 0.0, 0.0, 1.0);
        drawTriangle();
        //------------------------------------------------------------------------------
        break;
    case prespective:
        /*
            write code below:
            1- handle zoom in/out hint: glTranslatef
            2- handle spinning hint: glRotatef
            3- draw pyramid within frustum
            Recommended points:
            (0, 5, 0)
            (5, 0, 5)
            (5, 0, -5)
            (-5, 0, -5)
            (-5, 0, 5)
            you are encourged to change points location and observe its effects on rotation
        */
        // code here

        glTranslatef(0.0, 0.0, zOffset);
        spinY = currentSpin;
        glRotatef(spinY, 0.0, 1.0, 0.0);
        drawPyramid();
        //----------------------------------------------------
        break;
    default:
        break;
    }
    glFlush();
}
// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}
// spin logic
void spinDisplay(void)
{
    /*
        write code below:
        1- change currentSpin according to spinSpeed (note: spinSpeed unit is dgree/second)
        2- mark window to be rerendered (hint: glutPostRedisplay, prveTime)
    */
    // code here
    float elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = elapsedTime - prevTime;
    if (deltaTime > 1000)
    {
        prevTime = elapsedTime;
        return;
    }
    currentSpin += spinSpeed * (deltaTime / 1000.0);
    prevTime = elapsedTime;
    glutPostRedisplay();
    //------------------------------------------------------
}

void spinDisplayReverse(void)
{
    /*
        write code below:
        1- change currentSpin according to spinSpeed (note: spinSpeed unit is dgree/second)
        2- mark window to be rerendered
    */
    // code here
    float elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = elapsedTime - prevTime;
    if (deltaTime > 1000)
    {
        prevTime = elapsedTime;
        return;
    }
    currentSpin -= spinSpeed * (deltaTime / 1000.0);
    prevTime = elapsedTime;
    glutPostRedisplay();
    //---------------------------------------------------------------------
}

// keyboard & mouse
void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case CCW:
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(spinDisplay);
            spinning = true;
        }
        else if (state == GLUT_UP && !spinning)
        {
            stopSpinningDisplay();
        }
        break;
    case CW:
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(spinDisplayReverse);
            spinning = true;
        }
        else if (state == GLUT_UP && !spinning)
        {
            stopSpinningDisplay();
        }
        break;
    default:
        break;
    }
}
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case zoomIn:
        /*
        write code below:
            1- zoom in
            2- mark window for rerendering
        */
        // code here
        zOffset += 1.0; // Move object closer for perspective
        glutPostRedisplay();
        //--------------------------------------
        break;
    case zoomOut:
        /*
        write code below:
            1- zoom out
            2- mark window for rerendering
        */
        // code here
        zOffset -= 1.0; // Move object farther for perspective
        glutPostRedisplay();
        //--------------------------------------
        break;
    case stopSpinning:
        /*
        write code below:
            1- stop spinning (hint: use NULL)
        */
        // code here
        stopSpinningDisplay();
        spinning = false;   // Stop spinning
        glutIdleFunc(NULL); // Stop any ongoing idle function (spinning)
        //------------------------------------
        break;
    default:
        break;
    }
}
// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    switch (userChoice)
    {
    case ortho:
        /*
        write code below:
            1- initiate viewing box for parallel projection(use ortho variables (orthoLeft, orthoRight, ...))
        */
        // code here
        glOrtho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthoNear, orthoFar);
        //---------------------------------------------------------------
        break;
    case prespective:
        /*
        write code below:
            1- initiate frustum for perspective projection (use fru variables (fruLeft, fruRight, ...))
        */
        // code here
        glFrustum(fruLeft, fruRight, fruBottom, fruTop, fruNear, fruFar);
        //-----------------------------------------------------
        break;
    default:
        break;
    }

    glMatrixMode(GL_MODELVIEW);
}
// user interaction
void printUserInteraction()
{
    /*write code below:
     1- print user interaction(good practice)
    */
    // code here
    std::cout << "Controls:\n";
    std::cout << "Left Mouse Button: Spin counterclockwise\n";
    std::cout << "Right Mouse Button: Spin clockwise\n";
    std::cout << "Spacebar: Stop spinning\n";
    std::cout << "i: Zoom in\n";
    std::cout << "o: Zoom out\n";
    //---------------------------------------
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    printUserInteraction();
    std::cout << "Which projection type do you want\n1) parallel projection\n2) perspective projection\n>>\n Enter 1 or 2:";
    /*
    write code below:
        1- accept input from user and assign the value to userChoice variable
    */
    // code here
    std::cin >> userChoice;
    //---------------------------------------------------------------------
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(offsetX, offsetY);
    glutCreateWindow("Lab 2.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouse);
    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
// Note: At first user interaction, if scene spins unexpectadly you need to handle this behaviour (Hint: use prevTime variable)