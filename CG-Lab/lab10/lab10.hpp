#pragma once
#include "../ulti.hpp"

class Camera
{
protected:
	Point eye;

	Vector u, n, v;
	double view_angle, aspect, near_dist, far_dist;
	void rotate_axis(Vector& a, Vector& b, double angle);
public:
	Camera();
	void set(const Point& _eye, const Point& _look, const Vector& _up);
	void set_shape(double _view_angle, double _aspect, double _near_dist, double _far_dist);
	void slide(const double& du, const double& dv, const double& dn);

	void set_mv_matrix();
	void roll(double angle);
	void pitch(double angle);
	void yaw(double angle);
};

class CameraLab : public LabBase
{
protected:
	CameraLab(int argv, char* arg[]);
public:
	Camera camera;
	static void display();
	static void on_keyboard(unsigned char key, int x, int y);
	void init();
	void run();
	static CameraLab* get_instance(int argc, char* argv[]);
	~CameraLab();
};