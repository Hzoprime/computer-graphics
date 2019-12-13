
#include "Camera.h"

Camera cam;

void keyPressed(unsigned char key, int x, int y)
{
    switch (key) {
    case 'd': cam.slide(0.2, 0, 0); break;
    case 'a': cam.slide(-0.2, 0, 0); break;
    case 'w': cam.slide(0, 0.2, 0); break;
    case 's': cam.slide(0, -0.2, 0); break;
    case 'e': cam.slide(0, 0, 0.2); break;
    case 'q': cam.slide(0, 0, -0.2); break;
    case '-': cam.pitch(1); break;
    case '=': cam.pitch(-1); break;
    case '[': cam.yaw(1); break;
    case ']': cam.yaw(-1); break;
    case ';': cam.roll(1); break;
    case '\'': cam.roll(-1); break;
    case 27: exit(0);
    }
    glutPostRedisplay();
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    for (double i = -5; i < 5.1; i+=0.5) {
        if (i > -1e-6 && i < 1e-6) {
            glColor3f(1, 0, 0);
        }
        glVertex3f(-5, 0, i);
        glVertex3f(5, 0, i);
        glVertex3f(i, 0, -5);
        glVertex3f(i, 0, 5);
        if (i > -1e-6 && i < 1e-6) {

            glColor3f(0, 1, 0);
        }
    }
    glEnd();
    glColor3f(0, 0, 0);
    glutWireTeapot(1.0);
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("lab10");
    glutKeyboardFunc(keyPressed);
    glutDisplayFunc(draw);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glColor3f(0, 0, 0);
    glViewport(0, 0, 640, 480);
    cam.set(Point3(4, 4, 4), Point3(0, 0, 0), Vector3(0, 1, 0));
    cam.setShape(30.0, 64.0 / 48.0, 0.5, 50.0);
    glutMainLoop();
}