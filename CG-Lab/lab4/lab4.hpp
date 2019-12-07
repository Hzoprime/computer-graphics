#pragma once
#include "../ulti.hpp"
#include <thread>
#include <string>
#include <functional>
class Animation : public LabBase
{
protected:
	Animation(int argc, char* argv[]);
	vector<Point> poly1, poly2, poly3;
public:
	static void display();
	static void on_keyboard(unsigned char key, int x, int y);
	void init();
	void run();
	//static void animation();
	static void animation(int value);
	void interpolate(const int& n, const int& t);
	static Animation* get_instance(int argc, char* argv[]);
	~Animation();
};

