#pragma once
#include"../ulti.hpp"

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
		return a.x == b.x && a.y == b.y;
	}
};

class PolyLineApp : public LabBase
{
	int width = 500;
	int height = 500;
protected:
	PolyLineApp(int argc, char* argv[]);
	typedef vector<Point> Polyline;
	typedef vector<Point> Polygon;
	vector<Polyline> polylines;
	vector<Polygon> polygons;
	static char status;
	Point* dragged_point;
	Point* moving_point;
public:
	static void display();
	static void on_keyboard(unsigned char key, int x, int y);
	static void on_mouse(int button, int state, int x, int y);
	static void on_drag(int x, int y);
	static void on_move(int x, int y);
	void init();
	void run();
	Point near_to(double x, double y);
	Point get_new_point(double x, double y);
	void add_point(const Point& point);
	void delete_point(const Point& point);
	Point* get_near_point(const Point& point);
	static PolyLineApp* get_instance(int argc, char* argv[]);
	~PolyLineApp();
};
