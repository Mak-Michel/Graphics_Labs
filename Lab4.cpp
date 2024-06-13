#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <cmath>

using namespace std;

int userChoice;
float animationTimer = 0.0f;

typedef struct
{
    float x;
    float y;
} Vertex;

void drawLine_Bresenham(int x1, int y1, int x2, int y2, GLuint vao)
{
    std::vector<Vertex> vertices;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int stepX = (x1 < x2) ? 1 : -1;
    int StepY = (y1 < y2) ? 1 : -1;
    int p, succ1, succ2;
    int x = x1;
    int y = y1;
    if (dx > dy)
    {
        vertices.push_back({static_cast<float>(x), static_cast<float>(y)});
        p = 2 * dy - dx;
        succ1 = 2 * dy;
        succ2 = 2 * (dy - dx);
        for (int i = 0; i < dx; i++)
        {
            if (p < 0)
            {
                p += succ1;
            }
            else
            {
                y += StepY;
                p += succ2;
            }
            x += stepX;
            vertices.push_back({static_cast<float>(x), static_cast<float>(y)});
        }
    }
    else
    {
        vertices.push_back({static_cast<float>(x), static_cast<float>(y)});
        p = 2 * dx - dy;
        succ1 = 2 * dx;
        succ2 = 2 * (dx - dy);
        vertices.push_back({static_cast<float>(x), static_cast<float>(y)});
        for (int i = 0; i < dy; i++)
        {
            if (p < 0)
            {
                p += succ1;
            }
            else
            {
                x += stepX;
                p += succ2;
            }
            y += StepY;
            vertices.push_back({static_cast<float>(x), static_cast<float>(y)});
        }
    }

    glBindVertexArray(vao);

    // Create vertex buffer object (VBO) and bind it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Copy vertex data into VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Specify vertex attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    // Unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Draw using the VAO
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, vertices.size());
    glBindVertexArray(0);
}

void drawLine_DDA(int x1, int y1, int x2, int y2, GLuint vao)
{
    std::vector<Vertex> vertices;

    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x1;
    float y = y1;
    vertices.push_back({static_cast<float>(round(x)), static_cast<float>(round(y))});
    for (int i = 0; i < steps; i++)
    {
        x += xInc;
        y += yInc;
        vertices.push_back({static_cast<float>(round(x)), static_cast<float>(round(y))});
    }

    // Bind VAO
    glBindVertexArray(vao);

    // Create vertex buffer object (VBO) and bind it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Copy vertex data into VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Specify vertex attribute pointers
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    // Unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Draw using the VAO
    glBindVertexArray(vao);
    glDrawArrays(GL_POINTS, 0, vertices.size());
    glBindVertexArray(0);
}

// Function to calculate color according to animation timer
void getColor(float &red, float &green, float &blue)
{
    red = std::sin(animationTimer);
    green = std::cos(animationTimer);
    blue = 0.2f;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(6.0);

    // Generate and bind VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float r, g, b;
    animationTimer += 0.1f;

    switch (userChoice)
    {
    case 1:
        // Draw the letter 'M'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_DDA(50, 50, 70, 100, vao);
        drawLine_DDA(70, 100, 90, 85, vao);
        drawLine_DDA(90, 85, 110, 100, vao);
        drawLine_DDA(110, 100, 130, 50, vao);

        // Draw the letter 'A'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_DDA(150, 50, 175, 100, vao);
        drawLine_DDA(175, 100, 200, 50, vao);
        drawLine_DDA(164, 75, 187, 75, vao);

        // Draw the letter 'K'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_DDA(220, 50, 225, 100, vao);
        drawLine_DDA(224, 75, 250, 50, vao);
        drawLine_DDA(224, 75, 250, 100, vao);

        // Draw the letter 'A'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_DDA(270, 50, 295, 100, vao);
        drawLine_DDA(295, 100, 320, 50, vao);
        drawLine_DDA(284, 75, 307, 75, vao);

        // Draw the letter 'R'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_DDA(340, 50, 340, 100, vao);
        drawLine_DDA(340, 100, 370, 90, vao);
        drawLine_DDA(370, 90, 370, 75, vao);
        drawLine_DDA(340, 65, 370, 75, vao);
        drawLine_DDA(340, 65, 370, 50, vao);

        // Draw the letter 'I'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_DDA(390, 50, 390, 100, vao);
        drawLine_DDA(380, 100, 400, 100, vao);
        drawLine_DDA(380, 50, 400, 50, vao);

        // Draw the letter 'O'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_DDA(420, 70, 420, 80, vao);
        drawLine_DDA(420, 80, 430, 100, vao);
        drawLine_DDA(430, 100, 440, 100, vao);
        drawLine_DDA(440, 100, 450, 80, vao);
        drawLine_DDA(450, 70, 450, 80, vao);
        drawLine_DDA(420, 70, 430, 50, vao);
        drawLine_DDA(430, 50, 440, 50, vao);
        drawLine_DDA(440, 50, 450, 70, vao);
        break;
    case 2:
        // Draw the letter 'M'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_Bresenham(50, 50, 70, 100, vao);
        drawLine_Bresenham(70, 100, 90, 85, vao);
        drawLine_Bresenham(90, 85, 110, 100, vao);
        drawLine_Bresenham(110, 100, 130, 50, vao);

        // Draw the letter 'A'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_Bresenham(150, 50, 175, 100, vao);
        drawLine_Bresenham(175, 100, 200, 50, vao);
        drawLine_Bresenham(164, 75, 187, 75, vao);

        // Draw the letter 'K'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_Bresenham(220, 50, 225, 100, vao);
        drawLine_Bresenham(224, 75, 250, 50, vao);
        drawLine_Bresenham(224, 75, 250, 100, vao);

        // Draw the letter 'A'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_Bresenham(270, 50, 295, 100, vao);
        drawLine_Bresenham(295, 100, 320, 50, vao);
        drawLine_Bresenham(284, 75, 307, 75, vao);

        // Draw the letter 'R'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_Bresenham(340, 50, 340, 100, vao);
        drawLine_Bresenham(340, 100, 370, 90, vao);
        drawLine_Bresenham(370, 90, 370, 75, vao);
        drawLine_Bresenham(340, 65, 370, 75, vao);
        drawLine_Bresenham(340, 65, 370, 50, vao);

        // Draw the letter 'I'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_Bresenham(390, 50, 390, 100, vao);
        drawLine_Bresenham(380, 100, 400, 100, vao);
        drawLine_Bresenham(380, 50, 400, 50, vao);

        // Draw the letter 'O'
        getColor(r, g, b);
        glColor3f(r, g, b);
        drawLine_Bresenham(420, 70, 420, 80, vao);
        drawLine_Bresenham(420, 80, 430, 100, vao);
        drawLine_Bresenham(430, 100, 440, 100, vao);
        drawLine_Bresenham(440, 100, 450, 80, vao);
        drawLine_Bresenham(450, 70, 450, 80, vao);
        drawLine_Bresenham(420, 70, 430, 50, vao);
        drawLine_Bresenham(430, 50, 440, 50, vao);
        drawLine_Bresenham(440, 50, 450, 70, vao);
        break;
    }

    // Unbind VAO
    glBindVertexArray(0);

    glFlush();
}

void animate(int someValue) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, animate, 0);
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 150);
    glewExperimental = GL_TRUE;
    glewInit();

}

int main(int argc, char **argv)
{

    std::cout << "Enter: either 1 for DDA or 2 for Bresenham:" << std::endl;
    std::cin >> userChoice;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); // Adjusted window size
    glutCreateWindow("Makario Lab 4");
    glutTimerFunc(0, animate, 0);
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}