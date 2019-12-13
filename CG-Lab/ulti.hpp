#pragma once
#include<iostream>
#include<string>	
#include<algorithm>
#include<vector>
#include<map>	
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<deque>
#include<queue>
#include<stack>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::sort;
using std::max;
using std::min;
using std::vector;
using std::map;
using std::unordered_map;
using std::pair;
using std::make_pair;
using std::unordered_set;
using std::set;
using std::deque;
using std::queue;
using std::stack;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::cerr;
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
//#define _USE_MATH_DEFINES
#include <cmath>
const double pi = 3.14159265358979323846;
class LabBase
{
protected:
	int argc;
	char** argv;
	LabBase(int argc, char* argv[]);
	static unordered_map<int, LabBase*> instances;
public:
	virtual void run() = 0;
	~LabBase();
private:

};




enum Lab
{
	Lab1, Lab2, Lab3, Lab4, Lab5, Lab9, Lab10, Lab11
};


class Vector
{
public:
	double x;
	double y;
	double z;
	Vector(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {	}
	void set(const double& _x, const double& _y, const double& _z) { x = _x; y = _y; z = _z; }
	void set(const Vector& v) { x = v.x; y = v.y; z = v.z; }
	friend ostream& operator<<(ostream& out, const Vector& v) { return out << v.x << " " << v.y << " " << v.z; }
	friend Vector operator+(const Vector& a, const Vector& b) { return Vector(a.x + b.x, a.y + b.y, a.z + b.z); }
	friend Vector operator-(const Vector & a, const Vector & b) { return Vector(a.x - b.x, a.y - b.y, a.z - b.z); }
	friend Vector operator*(const double& a, const Vector & b) { return Vector(a * b.x, a * b.y, a * b.z); }
	friend Vector cross_product(const Vector & a, const Vector & b)
	{
		return Vector(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}
	friend double dot_product(const Vector & a, const Vector & b) { return a.x* b.x + a.y * b.y + a.z * b.z; }
	void normalize()
	{
		double norm = dot_product(*this, *this);
		if (norm <= std::numeric_limits<double>::epsilon())
		{
			cerr << "this vector might be (0, 0, 0)" << endl;
			return;
		}
		double factor = 1.0 / sqrt(norm);
		x *= factor;
		y *= factor;
		z *= factor;
	}
};

class Point
{
public:
	double x;
	double y;
	double z;
	Point(double _x = 0, double _y = 0, double _z = 0) :x(_x), y(_y), z(_z) {}
	void set(const double& _x, const double& _y, const double& _z) { x = _x; y = _y; z = _z; }
	void set(const Point& p) { x = p.x; y = p.y; z = p.z; }
	friend ostream& operator<<(ostream& out, const Point& p) { return out << p.x << " " << p.y << " " << p.z; }
	friend bool operator==(const Point& a, const Point& b)
	{
		return abs(a.x - b.x) < std::numeric_limits<double>::epsilon() && (a.y - b.y) < std::numeric_limits<double>::epsilon();
	}
	// two  function below are used linear interpolation
	friend Point operator+(const Point & a, const Point & b) { return Point(a.x + b.x, a.y + b.y, a.z + b.z); }
	friend Point operator*(const double& m, const Point & a) { return Point(m * a.x, m * a.y, m * a.z); }
	friend Vector get_diff(const Point& a, const Point& b)
	{
		return (Vector(a.x - b.x, a.y - b.y, a.z - b.z));
	}
};

const Point origin;



class Line
{
public:
	Point start;
	Point end;
	Line(const Point& _start = origin, const Point& _end = origin) :start(_start), end(_end)
	{

	}
	void draw_in_gl()const
	{
		glBegin(GL_LINES);
		glVertex2d(start.x, start.y);
		glVertex2d(end.x, end.y);
		glEnd();
	}
	friend ostream& operator<<(ostream& out, const Line& line)
	{
		return out << "start: " << line.start << "\tend: " << line.end;
	}
};

class Rect
{
public:
	Point points[4];
	Rect(const Point& p1, const Point& p2)
	{
		set_diagonal_point(p1, p2);
	}
	void draw_in_gl()
	{
		glBegin(GL_LINE_LOOP);

		for (auto& point : points)
		{
			glVertex2d(point.x, point.y);
		}
		glEnd();
	}
	void set_diagonal_point(const Point& p1, const Point& p2)
	{
		points[0] = p1;
		points[2] = p2;
		points[1] = Point(p1.x, p2.y);
		points[3] = Point(p2.x, p1.y);
	}
};


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