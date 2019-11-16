#pragma once
#include"../ulti.hpp"

class CSClipper : public LabBase
{
public:
	static void display();
	void init();
	void run();
	static CSClipper* get_instance(int argc, char* argv[]);
	~CSClipper();
protected:
	CSClipper(int argc, char* argv[]);
};