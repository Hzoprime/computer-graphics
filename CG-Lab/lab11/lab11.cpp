#include "lab11.hpp"

CameraLab2::CameraLab2(int argv, char* arg[]) :LabBase(argv, arg), mode(0)
{
	v.push_back(new double[16]);
	v.push_back(new double[16]);
}

void CameraLab2::transform_matrix(const int& id, unsigned char key)
{
	glPushMatrix();
	glLoadMatrixd(v[id]);
	switch (key)
	{
	case 'a': glTranslated(-0.1, 0, 0); break;
	case 'd': glTranslated(0.1, 0, 0); break;
	case 's': glTranslated(0, 0, 0.1); break;
	case 'w': glTranslated(0, 0, -0.1); break;
	case 'q': glTranslated(0, 0.1, 0); break;
	case 'e': glTranslated(0, -0.1, 0); break;
	case '-': glRotated(1, 1, 0, 0); break;
	case '=': glRotated(-1, 1, 0, 0); break;
	case '[': glRotated(1, 0, 1, 0); break;
	case ']': glRotated(-1, 0, 1, 0); break;
	case ';': glRotated(1, 0, 0, 1); break;
	case '\'': glRotated(-1, 0, 0, 1); break;
	case 27: glutLeaveMainLoop();
	}
	glGetDoublev(GL_MODELVIEW_MATRIX, v[id]);
	glPopMatrix();
}

void CameraLab2::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(0, 1, 0);
	glBegin(GL_LINES);
	for (double i = -5; i < 5.1; i += 0.5)
	{
		if (i > -1e-6 && i < 1e-6)
		{
			glColor3d(1, 0, 0);
		}
		glVertex3d(-5, 0, i);
		glVertex3d(5, 0, i);
		glVertex3d(i, 0, -5);
		glVertex3d(i, 0, 5);
		if (i > -1e-6 && i < 1e-6)
		{

			glColor3d(0, 1, 0);
		}
	}
	glEnd();
	glColor3d(0, 0, 0);

	auto instance = get_instance(0, 0);
	for (auto& matrix : instance->v)
	{
		glPushMatrix();
		glMultMatrixd(matrix);
		glutWireTeapot(1.0);
		glPopMatrix();
	}
	glFlush();
	glutSwapBuffers();
}

void CameraLab2::on_keyboard(unsigned char key, int x, int y)
{
	auto instance = get_instance(0, 0);
	if (key >= '0' && key < '9')
	{
		instance->mode = key - '0';
	}
	auto& camera = instance->camera;
	switch (instance->mode)
	{
	default:
		instance->transform_matrix(instance->mode - 1, key);
		break;
	case 0:
		switch (key)
		{
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
		case 27: glutLeaveMainLoop();
		}
		break;
	}
	glutPostRedisplay();
}

void CameraLab2::init()
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
	for (auto& matrix : v)
	{
		glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
	}
	camera.set_shape(30.0, 64.0 / 48.0, 0.5, 50.0);
	camera.set(Point(4, 4, 4), Point(0, 0, 0), Vector(0, 1, 0));
}

void CameraLab2::run()
{
	init();
	glFlush();
	glutMainLoop();
}

CameraLab2* CameraLab2::get_instance(int argc, char* argv[])
{
	if (instances.count(Lab11))
	{
		return dynamic_cast<CameraLab2*>(instances[Lab11]);
	}
	auto instance = new CameraLab2(argc, argv);
	instances[Lab11] = instance;
	return instance;
}

CameraLab2::~CameraLab2()
{
	instances.erase(Lab10);
}
