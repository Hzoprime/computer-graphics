#pragma once
#include "../ulti.hpp"

class CameraLab2 : public LabBase
{
protected:
	CameraLab2(int argv, char* arg[]);
	int mode;
	vector<double*> v;
public:
	void transform_matrix(const int& id, unsigned char key);
	Camera camera;
	static void display();
	static void on_keyboard(unsigned char key, int x, int y);
	void init();
	void run();
	static CameraLab2* get_instance(int argc, char* argv[]);
	~CameraLab2();
};
