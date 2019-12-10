#pragma once
#include "../ulti.hpp"

class CyrusBeckClipper : public LabBase
{
	typedef Vector normal;
	typedef pair<normal, Point> NormalLine;
protected:
	CyrusBeckClipper(int argc, char* argv[]);
	vector<Line> random_line_list;
	vector<Line> clipped_line_list;
	vector<Point> polygon_points;
	vector<NormalLine> polygon_normal_lines;
	int boundary;
	bool adding_point;
	void get_normal_line();
public:
	void randomize_line_list();
	void clip();
	static void display();
	void init();
	void run();
	static void on_mouse(int button, int state, int x, int y);
	static void on_keyboard(unsigned char key, int x, int y);
	static CyrusBeckClipper* get_instance(int argc, char* argv[]);
	~CyrusBeckClipper();
};
