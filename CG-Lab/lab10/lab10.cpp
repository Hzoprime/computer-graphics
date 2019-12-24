#include "lab10.hpp"

CameraLab::CameraLab(int argv, char* arg[]) :LabBase(argc, arg)
{
}

void CameraLab::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(0, 1, 0);
	glBegin(GL_LINES);
	for (double i = -5; i < 5.1; i += 0.5) {
		if (i > -1e-6 && i < 1e-6) {
			glColor3d(1, 0, 0);
		}
		glVertex3d(-5, 0, i);
		glVertex3d(5, 0, i);
		glVertex3d(i, 0, -5);
		glVertex3d(i, 0, 5);
		if (i > -1e-6 && i < 1e-6) {

			glColor3d(0, 1, 0);
		}
	}
	glEnd();
	glColor3d(0, 0, 0);
	glutWireTeapot(1.0);
	glFlush();
	glutSwapBuffers();
}

void CameraLab::on_keyboard(unsigned char key, int x, int y)
{
	auto& camera = get_instance(0, 0)->camera;
	switch (key) {
	case 'd': camera.slide(0.2, 0, 0); break;
	case 'a': camera.slide(-0.2, 0, 0); break;
	case 'w': camera.slide(0, 0, -0.2); break;
	case 's': camera.slide(0, 0, 0.2); break;
	case '\'': camera.slide(0, 0.2, 0); break;
	case ';': camera.slide(0, -0.2, 0); break;
	case '-': camera.pitch(1); break;
	case '=': camera.pitch(-1); break;
	case '[': camera.yaw(-1); break;
	case ']': camera.yaw(1); break;
	case 'q': camera.roll(1); break;
	case 'e': camera.roll(-1); break;
	case 27: glutLeaveMainLoop(); break;
	}
	glutPostRedisplay();
}

void CameraLab::init()
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("lab10");
	glutKeyboardFunc(on_keyboard);
	glutDisplayFunc(display);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glColor3f(0, 0, 0);
	glViewport(0, 0, 640, 480);
	camera.set_shape(30.0, 64.0 / 48.0, 0.5, 50.0);
	camera.set(Point(4, 4, 4), Point(0, 0, 0), Vector(0, 1, 0));
}

void CameraLab::run()
{
	init();
	glFlush();
	glutMainLoop();
}

CameraLab* CameraLab::get_instance(int argc, char* argv[])
{
	if (instances.count(Lab10))
	{
		return dynamic_cast<CameraLab*>(instances[Lab10]);
	}
	auto instance = new CameraLab(argc, argv);
	instances[Lab10] = instance;
	return instance;
}

CameraLab::~CameraLab()
{
	instances.erase(Lab10);
}
