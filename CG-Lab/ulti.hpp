#pragma once
#include<iostream>
#include<string>	
#include<algorithm>
#include<vector>
#include<map>	
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<deque>
#include<queue>
#include<stack>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::sort;
using std::max;
using std::min;
using std::vector;
using std::map;
using std::unordered_map;
using std::unordered_set;
using std::set;
using std::deque;
using std::queue;
using std::stack;
using std::ostream;
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
//#define _USE_MATH_DEFINES
#include <cmath>
const double pi = 3.14159265358979323846;
class LabBase
{
protected:
	int argc;
	char** argv;
	LabBase(int argc, char* argv[]);
	static unordered_map<int, LabBase*> instances;
public:
	virtual void run() = 0;
	~LabBase();
private:

};
enum Lab
{
	Lab1, Lab2, Lab3
};


