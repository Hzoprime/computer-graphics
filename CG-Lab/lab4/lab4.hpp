#pragma once
#include "../ulti.hpp"
class Animation : public LabBase
{
protected:
	Animation(int argc, char* argv[]);
	vector<Point> poly1, poly2;
public:
	static void display();
	static void on_keyboard(unsigned char key, int x, int y);
	void init();
	void run();
	static Animation* get_instance(int argc, char* argv[]);
	~Animation();
};

