#include"lab3.hpp"

void CSClipper::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);

	glVertex2d(origin.x, origin.y); 
	glVertex2d(10, 0); 
	glVertex2d(5, 5*sqrt(3));


	glEnd();
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
	glutCreateWindow("DrawSinOverX");
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

CSClipper::~CSClipper()
{
	instances.erase(Lab3);
}

CSClipper::CSClipper(int argc, char* argv[]) : LabBase(argc, argv)
{

}
