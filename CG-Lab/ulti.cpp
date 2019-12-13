#include"ulti.hpp"
LabBase::LabBase(int _argc, char* _argv[]) : argc(_argc), argv(_argv)
{
}

LabBase::~LabBase()
{
}

unordered_map<int, LabBase*> LabBase::instances;
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

