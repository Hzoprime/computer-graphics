#pragma once
#include "../ulti.hpp"



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
