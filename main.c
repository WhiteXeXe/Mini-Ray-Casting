#include <GL/freeglut.h>
#include "stdio.h"
#include <stdbool.h>
#include <math.h>

#define ESCAPE '\033'
#define CNTPOINTS 180
#define LENGTH 200

float mouseX = 0.0f;
float mouseY = 0.0f;
bool flagDrawDetails = 0;
int chooseBlock = 0; // 0 - block
                     // 1 - horizontal line
                     // 2 - vertical line
int start_or_not = 0;
int locBlock[16][20] = { 0 };



int checkPos(int x, int y, double angle) {
       
    double newX, newY;
    int normX, normY, i;
    for (i = 0; i < 200; i++) {
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < 20; k++) {

                if (locBlock[j][k] == 1) {

                    normX = k * 25;               // странно работает, но работает 
                    normY = 400 - j * 25;

                    newX = mouseX + i * cos(angle);
                    newY = mouseY + i * sin(angle);

                    if (newY >= normY - 25 && newY <= normY && newX >= normX && newX <= normX + 25) {
                        return i;
                    }
                }
            }
        }
    }
    return i;
}



void drawLight() {

 
    glBegin(GL_POINTS);
    glVertex3f(mouseX, mouseY, 0);
    glEnd();


    int degrees = 0;                // рисование круга вокруг мыши
    double newX, newY;

    glColor3f(1, 0, 0);
    glPointSize(2);
    glBegin(GL_LINES);
    for (int i = 0; i < CNTPOINTS; i++) {
        double angle = degrees * 3.1415 / 180;

        glVertex3f(mouseX, mouseY, 0);

        int size = checkPos(mouseX, mouseY, angle);

        newX = mouseX + size * cos(angle);
        newY = mouseY + size * sin(angle);


        glVertex3f(newX, newY, 0);

        degrees += 360 / CNTPOINTS;
    }
    glEnd();
    glColor3f(1, 1, 1);
    glPointSize(1);

    
    
}



void drawMinLines() {
    glBegin(GL_LINES);

    for (float x = 125; x < 375; x += 12.5) {
        glVertex3f(x, 100, 0);
        glVertex3f(x, 300, 0);
    }

    for (float y = 100; y < 300; y += 12.5) {
        glVertex3f(125, y, 0);
        glVertex3f(375, y, 0);
    }

    glEnd();
}

void drawFullMap() {
    glColor3f(0, 0, 0);

    glBegin(GL_POLYGON);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 20; j++) {
            if (locBlock[i][j] == 1) {
                float x = 125 + 25 * j;
                float y = 300 - 25 * i;

                glVertex3f(x, y, 0);
                glVertex3f(x + 25, y, 0);
                glVertex3f(x + 25, y - 25, 0);
                glVertex3f(x, y - 25, 0);
            }
        }
    }
    glEnd();

    glColor3f(1, 1, 1);

    glBegin(GL_LINES);
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 20; j++) {
            if (locBlock[i][j] == 1) {
                float x = 25 * j;
                float y = 400 - 25 * i;


                if (i == 0 || locBlock[i - 1][j] == 0) {
                    glVertex3f(x, y, 0);
                    glVertex3f(x + 25, y, 0);
                }
                if (i == 15 || locBlock[i + 1][j] == 0) {
                    glVertex3f(x, y - 25, 0);
                    glVertex3f(x + 25, y - 25, 0);
                }
                if (j == 0 || locBlock[i][j - 1] == 0) {
                    glVertex3f(x, y, 0);
                    glVertex3f(x, y - 25, 0);
                }
                if (j == 19 || locBlock[i][j + 1] == 0) {
                    glVertex3f(x + 25, y, 0);
                    glVertex3f(x + 25, y - 25, 0);
                }
            }
        }
    }
    glEnd();
}

void drawText(const char* text, float x, float y, void* font) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(font, *text);
        text++;
    }
}

void drawMinMapANDButton() {

    glLineWidth(2);

    glColor3f(1, 1, 1);

    glBegin(GL_LINES);
    // mainMiniWindow
    glVertex3f(125, 100, 0);
    glVertex3f(125, 300, 0);

    glVertex3f(125, 300, 0);
    glVertex3f(375, 300, 0);

    glVertex3f(375, 300, 0);
    glVertex3f(375, 100, 0);

    glVertex3f(375, 100, 0);
    glVertex3f(125, 100, 0);
    glEnd();

    // button1
    glBegin(GL_LINES);
    glVertex3f(100, 25, 0);
    glVertex3f(150, 25, 0);

    glVertex3f(150, 25, 0);
    glVertex3f(150, 75, 0);

    glVertex3f(150, 75, 0);
    glVertex3f(100, 75, 0);

    glVertex3f(100, 75, 0);
    glVertex3f(100, 25, 0);
    glEnd();

    // symbol1
    glBegin(GL_POLYGON);
    glVertex3f(118.75, 43.75, 0);
    glVertex3f(131.25, 43.75, 0);

    glVertex3f(131.25, 43.75, 0);
    glVertex3f(131.25, 56.25, 0);

    glVertex3f(131.25, 56.25, 0);
    glVertex3f(118.75, 56.25, 0);

    glVertex3f(118.75, 56.25, 0);
    glVertex3f(118.75, 43.75, 0);
    glEnd();

    // button2
    glBegin(GL_LINES);
    glVertex3f(225, 25, 0);
    glVertex3f(275, 25, 0);

    glVertex3f(275, 25, 0);
    glVertex3f(275, 75, 0);

    glVertex3f(275, 75, 0);
    glVertex3f(225, 75, 0);

    glVertex3f(225, 75, 0);
    glVertex3f(225, 25, 0);
    glEnd();

    // symbol2
    glBegin(GL_POLYGON);
    glVertex3f(237.5, 43.75, 0);
    glVertex3f(262.5, 43.75, 0);

    glVertex3f(262.5, 43.75, 0);
    glVertex3f(262.5, 56.25, 0);

    glVertex3f(262.5, 56.25, 0);
    glVertex3f(237.5, 56.25, 0);

    glVertex3f(237.5, 56.25, 0);
    glVertex3f(237.5, 43.75, 0);
    glEnd();

    // button3
    glBegin(GL_LINES);
    glVertex3f(350, 25, 0);
    glVertex3f(400, 25, 0);

    glVertex3f(400, 25, 0);
    glVertex3f(400, 75, 0);

    glVertex3f(400, 75, 0);
    glVertex3f(350, 75, 0);

    glVertex3f(350, 75, 0);
    glVertex3f(350, 25, 0);
    glEnd();

    // symbol3
    glBegin(GL_POLYGON);
    glVertex3f(368.75, 37.5, 0);
    glVertex3f(381.25, 37.5, 0);

    glVertex3f(381.25, 37.5, 0);
    glVertex3f(381.25, 62.5, 0);

    glVertex3f(381.25, 62.5, 0);
    glVertex3f(368.75, 62.5, 0);

    glVertex3f(368.75, 62.5, 0);
    glVertex3f(368.75, 37.5, 0);
    glEnd();

    // startButton
    glBegin(GL_LINES);
    glVertex3f(200, 325, 0);
    glVertex3f(300, 325, 0);

    glVertex3f(300, 325, 0);
    glVertex3f(300, 375, 0);

    glVertex3f(300, 375, 0);
    glVertex3f(200, 375, 0);

    glVertex3f(200, 375, 0);
    glVertex3f(200, 325, 0);

    glEnd();

}

void drawMapBlocks() {
    if (chooseBlock == 0) {

        if (flagDrawDetails == 1) {
            int xCoord = (mouseX - 125) / 12.5;
            int yCoord = (300 - mouseY) / 12.5;
            if (locBlock[yCoord][xCoord] == 1) {
                locBlock[yCoord][xCoord] = 0;
            }
            else {
                locBlock[yCoord][xCoord] = 1;
            }
        }

    }
    if (chooseBlock == 1) {

        if (flagDrawDetails == 1) {
            int xCoord = (mouseX - 125) / 12.5;
            int yCoord = (300 - mouseY) / 12.5;

            if (xCoord - 1 >= 0 && xCoord + 1 <= 19) {
                if (locBlock[yCoord][xCoord] == 1) {
                    locBlock[yCoord][xCoord] = 0;
                    locBlock[yCoord][xCoord + 1] = 0;
                    locBlock[yCoord][xCoord - 1] = 0;
                }
                else {
                    locBlock[yCoord][xCoord] = 1;
                    locBlock[yCoord][xCoord + 1] = 1;
                    locBlock[yCoord][xCoord - 1] = 1;
                }
            }
        }

    }
    if (chooseBlock == 2) {

        if (flagDrawDetails == 1) {
            int xCoord = (mouseX - 125) / 12.5;
            int yCoord = (300 - mouseY) / 12.5;

            if (yCoord - 1 >= 0) {
                if (locBlock[yCoord][xCoord] == 1) {
                    locBlock[yCoord][xCoord] = 0;
                    locBlock[yCoord + 1][xCoord] = 0;
                    locBlock[yCoord - 1][xCoord] = 0;
                }
                else {
                    locBlock[yCoord][xCoord] = 1;
                    locBlock[yCoord + 1][xCoord] = 1;
                    locBlock[yCoord - 1][xCoord] = 1;
                }
            }
        }

    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 20; j++) {
            if (locBlock[i][j] == 1) {
                float x = 125 + (12.5 * j);
                float y = 300 - (12.5 * i);
                glColor3f(1, 1, 1);
                glBegin(GL_POLYGON);

                glVertex3f(x, y, 0);
                glVertex3f(x + 12.5, y, 0);
                glVertex3f(x + 12.5, y - 12.5, 0);
                glVertex3f(x, y - 12.5, 0);

                glEnd();
            }
        }
    }
}

void drawPickBlock() {
    if (chooseBlock == 0) {
        glColor3f(1, 1, 1);

        // button1
        glBegin(GL_POLYGON);
        glVertex3f(100, 25, 0);
        glVertex3f(150, 25, 0);

        glVertex3f(150, 25, 0);
        glVertex3f(150, 75, 0);

        glVertex3f(150, 75, 0);
        glVertex3f(100, 75, 0);

        glVertex3f(100, 75, 0);
        glVertex3f(100, 25, 0);
        glEnd();

        // symbol1
        glColor3f(0, 0, 0);
        glBegin(GL_POLYGON);
        glVertex3f(118.75, 43.75, 0);
        glVertex3f(131.25, 43.75, 0);

        glVertex3f(131.25, 43.75, 0);
        glVertex3f(131.25, 56.25, 0);

        glVertex3f(131.25, 56.25, 0);
        glVertex3f(118.75, 56.25, 0);

        glVertex3f(118.75, 56.25, 0);
        glVertex3f(118.75, 43.75, 0);
        glEnd();
    }
    if (chooseBlock == 1) {
        glColor3f(1, 1, 1);

        // button2
        glBegin(GL_POLYGON);
        glVertex3f(225, 25, 0);
        glVertex3f(275, 25, 0);

        glVertex3f(275, 25, 0);
        glVertex3f(275, 75, 0);

        glVertex3f(275, 75, 0);
        glVertex3f(225, 75, 0);

        glVertex3f(225, 75, 0);
        glVertex3f(225, 25, 0);
        glEnd();

        // symbol2
        glColor3f(0, 0, 0);
        glBegin(GL_POLYGON);
        glVertex3f(237.5, 43.75, 0);
        glVertex3f(262.5, 43.75, 0);

        glVertex3f(262.5, 43.75, 0);
        glVertex3f(262.5, 56.25, 0);

        glVertex3f(262.5, 56.25, 0);
        glVertex3f(237.5, 56.25, 0);

        glVertex3f(237.5, 56.25, 0);
        glVertex3f(237.5, 43.75, 0);
        glEnd();
    }
    if (chooseBlock == 2) {
        // button3
        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
        glVertex3f(350, 25, 0);
        glVertex3f(400, 25, 0);

        glVertex3f(400, 25, 0);
        glVertex3f(400, 75, 0);

        glVertex3f(400, 75, 0);
        glVertex3f(350, 75, 0);

        glVertex3f(350, 75, 0);
        glVertex3f(350, 25, 0);
        glEnd();

        // symbol3
        glColor3f(0, 0, 0);
        glBegin(GL_POLYGON);
        glVertex3f(368.75, 37.5, 0);
        glVertex3f(381.25, 37.5, 0);

        glVertex3f(381.25, 37.5, 0);
        glVertex3f(381.25, 62.5, 0);

        glVertex3f(381.25, 62.5, 0);
        glVertex3f(368.75, 62.5, 0);

        glVertex3f(368.75, 62.5, 0);
        glVertex3f(368.75, 37.5, 0);
        glEnd();
    }
}

bool checkZoneForMenu(int x, int y) {
    if ((x > 125 && x < 375) && (y > 100 && y < 300)) return 1;
    if ((x > 100 && x < 150) && (y > 325 && y < 375)) {
        chooseBlock = 0;
        return 1;
    }
    if ((x > 225 && x < 275) && (y > 325 && y < 375)) {
        chooseBlock = 1;
        return 1;
    }
    if ((x > 350 && x < 400) && (y > 325 && y < 375)) {
        chooseBlock = 2;
        return 1;
    }
    if ((x > 200 && x < 300) && (y > 25 && y < 75)) {
        start_or_not = 1;
        return 1;
    }
    else return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

 
 
    if (start_or_not == 0) {
        drawMinMapANDButton();
        drawMinLines();
        glColor3f(1, 1, 1);
        drawText("GO", 235, 343, GLUT_BITMAP_HELVETICA_18);
        drawMapBlocks();
        drawPickBlock();
    }
    if (start_or_not == 1) {
        drawFullMap();
        drawLight();
    }

    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y) {
    if (checkZoneForMenu(x, y) == 1 && state == GLUT_DOWN) {

        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        mouseX = (float)x;
        mouseY = (float)(windowHeight - y);

        flagDrawDetails = 1;
        glutPostRedisplay();
    }
    else {
        if (state == GLUT_UP) flagDrawDetails = 0;
    }
}

void mouseMotion(int x, int y) {

    glutPostRedisplay();

    if (start_or_not == 1) {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        mouseX = x;
        mouseY = (float)(windowHeight - y);
    }

    printf("%d %d\n", x, y);
}

void setupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case ESCAPE:
        start_or_not = 0;
        glutPostRedisplay();
        break;
    }
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 400);
    glutInitWindowPosition(600, 300);
    glutCreateWindow("Mini-Ray_Casting");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutDisplayFunc(display);
    // glutSetCursor(GLUT_CURSOR_NONE);  // ДЛЯ ТОГО, ЧТОБЫ СКРЫВАТЬ МЫШЬ!!!!!!
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    setupProjection();
    glutMainLoop();

    return 0;
}