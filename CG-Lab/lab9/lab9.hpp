#pragma once
#include "../ulti.hpp"

class Mesh
{

};


class MeshLab : public LabBase
{
protected:
	MeshLab(int argc, char* argv[]);
	double boundary;
public:

	static void display();
	void init();
	void run();
	//static void on_mouse(int button, int state, int x, int y);
	static void on_keyboard(unsigned char key, int x, int y);
	static MeshLab* get_instance(int argc, char* argv[]);
	~MeshLab();
};
