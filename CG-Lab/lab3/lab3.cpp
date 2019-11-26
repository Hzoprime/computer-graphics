#include"lab3.hpp"





void CSClipper::display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	auto instance = get_instance(0, 0);
	instance->rect.draw_in_gl();
	


	glFlush();
}

void CSClipper::init()
{
	glutInit(&argc, argv);
	//glut 初始化 为 rgb颜色模式,单缓冲
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//glut窗体创建
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("CSClipper");
	// 设置绘制函数
	glutDisplayFunc(display);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	gluOrtho2D(-20.0, 20.0, -20.0, 20.0);
}

void CSClipper::run()
{
	init();
	glutMainLoop();
}

CSClipper* CSClipper::get_instance(int argc, char* argv[])
{
	if (instances.count(Lab3))
	{
		return dynamic_cast<CSClipper*>(instances[Lab3]);
	}
	auto instance = new CSClipper(argc, argv);
	instances[Lab3] = instance;
	return instance;
}

void CSClipper::clip()
{
	double boandary[4];
	int code[4];
	for (auto& line : raw_lines)
	{

	}
}

CSClipper::~CSClipper()
{
	instances.erase(Lab3);
}

CSClipper::CSClipper(int argc, char* argv[]) : LabBase(argc, argv), rect(Point(0, 0), Point(6, 6))
{
	raw_lines.push_back(Line(Point(rand() % 10, rand() % 10), Point(rand() % 10, rand() % 10)));
	raw_lines.push_back(Line(Point(rand() % 10, rand() % 10), Point(rand() % 10, rand() % 10)));
	raw_lines.push_back(Line(Point(rand() % 10, rand() % 10), Point(rand() % 10, rand() % 10)));
	raw_lines.push_back(Line(Point(rand() % 10, rand() % 10), Point(rand() % 10, rand() % 10)));
}
