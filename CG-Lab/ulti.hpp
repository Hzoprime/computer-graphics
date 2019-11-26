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
	Lab1, Lab2, Lab3
};


class Point
{
public:
	double x;
	double y;
	Point(double _x = 0, double _y = 0) :x(_x), y(_y) {}
	friend ostream& operator<<(ostream& out, const Point& p)
	{
		return out << '(' << p.x << ", " << p.y << ')';
	}
	friend bool operator==(const Point& a, const Point& b)
	{
		return abs(a.x - b.x) < std::numeric_limits<double>::epsilon() && (a.y - b.y) < std::numeric_limits<double>::epsilon();
	}
};

const Point origin;

class Line
{
public:
	Point start;
	Point end;
	Line(const Point& _start = origin, const Point& _end = origin):start(_start), end(_end)
	{

	}
	void draw_in_gl()
	{
		glBegin(GL_LINE);
		glVertex2d(start.x, start.y);
		glVertex2d(end.x, end.y);
		glEnd();
	}
};

class Rect
{
	Point points[4];
public:
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
			cout << point << endl;
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
