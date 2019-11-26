#pragma once
#include"../ulti.hpp"






class CSClipper : public LabBase
{
public:
	static void display();
	void init();
	void run();
	static CSClipper* get_instance(int argc, char* argv[]);
	void clip();
	~CSClipper();
protected:
	Rect rect;
	vector<Line> raw_lines;
	vector<Line> clipped_lines;
	vector<Point> points;
	vector<Point> clipped_points;
	CSClipper(int argc, char* argv[]);
};

