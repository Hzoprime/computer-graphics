#include "lab10.hpp"


void Camera::rotate_axis(Vector& a, Vector& b, double angle)
{
	double radian = pi / 180 * angle;
	double cosine = cos(radian), sine = sin(radian);
	Vector a_prime = cosine * a - sine * b;
	Vector b_prime = sine * a + cosine * b;
	a = a_prime;
	b = b_prime;
}

Camera::Camera() :view_angle(0), aspect(0), near_dist(0), far_dist(0)
{

}

void Camera::set(const Point& _eye, const Point& _look, const Vector& _up)
{
	eye = _eye;
	n = get_diff(_eye, _look);
	u = cross_product(_up, n);
	v = cross_product(n, u);
	u.normalize();
	v.normalize();
	n.normalize();
	set_mv_matrix();
}

void Camera::set_shape(double _view_angle, double _aspect, double _near_dist, double _far_dist)
{
	view_angle = _view_angle;
	aspect = _aspect;
	near_dist = _near_dist;
	far_dist = _far_dist;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(view_angle, aspect, near_dist, far_dist);
}

void Camera::slide(const double& du, const double& dv, const double& dn)
{
	eye.x += du * u.x + dv * v.x + dn * n.x;
	eye.y += du * u.y + dv * v.y + dn * n.y;
	eye.z += du * u.z + dv * v.z + dn * n.z;
	set_mv_matrix();
}

void Camera::set_mv_matrix()
{
	double m[16];
	Vector eye_vector(eye.x, eye.y, eye.z);
	m[0] = u.x; m[4] = u.y; m[8] = u.z;     m[12] = -dot_product(eye_vector, u);
	m[1] = v.x; m[5] = v.y; m[9] = v.z;     m[13] = -dot_product(eye_vector, v);
	m[2] = n.x; m[6] = n.y; m[10] = n.z;    m[14] = -dot_product(eye_vector, n);
	m[3] = 0;   m[7] = 0;   m[11] = 0;      m[15] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(m);
}

void Camera::roll(double angle)
{
	rotate_axis(u, v, angle);
	set_mv_matrix();
}

void Camera::pitch(double angle)
{
	rotate_axis(v, n, angle);
	set_mv_matrix();
}

void Camera::yaw(double angle)
{
	rotate_axis(n, u, angle);
	set_mv_matrix();
}

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
	cout << key << endl;
	cout << (int)key << endl;
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
	case 27: exit(0);
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
