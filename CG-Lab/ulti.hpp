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
	Lab1, Lab2, Lab3, Lab4, Lab5, Lab9
};



class Point
{
public:
	double x;
	double y;
	double z;
	Point(double _x = 0, double _y = 0, double _z = 0) :x(_x), y(_y), z(_z) {}
	friend ostream& operator<<(ostream& out, const Point& p)
	{
		return out << '(' << p.x << ", " << p.y << ')';
	}
	friend bool operator==(const Point& a, const Point& b)
	{
		return abs(a.x - b.x) < std::numeric_limits<double>::epsilon() && (a.y - b.y) < std::numeric_limits<double>::epsilon();
	}
	friend Point operator+(const Point & a, const Point & b)
	{
		return Point(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	friend Point operator*(const double& m, const Point & a)
	{
		return Point(m * a.x, m * a.y, m * a.z);
	}
};

const Point origin;

class Vector
{
public:
	double x;
	double y;
	double z;
	Vector(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z)
	{

	}
	friend Vector operator+(const Vector& a, const Vector& b)
	{
		return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	friend Vector operator-(const Vector & a, const Vector & b)
	{
		return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	friend Vector operator*(const double& a, const Vector & b)
	{
		return Vector(a * b.x, a * b.y, a * b.z);
	}
	friend Vector cross_product(const Vector & a, const Vector & b)
	{
		return Vector(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}
	friend double dot_product(const Vector & a, const Vector & b)
	{
		return a.x* b.x + a.y * b.y + a.z * b.z;
	}
};

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


