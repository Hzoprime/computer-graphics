#pragma once
#include "../ulti.hpp"
class DrawSinOverX : public LabBase
{
protected:
	static double a, b, c, d;
	DrawSinOverX(int argc, char* argv[]);
public:
	static void display();
	static void on_keyboard(unsigned char key, int x, int y);
	void init();
	void run();
	static DrawSinOverX* get_instance(int argc, char* argv[]);
	~DrawSinOverX();
};
