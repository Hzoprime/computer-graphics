#include"lab1.hpp"

double DrawSinOverX::a = 1;
double DrawSinOverX::b = 2;
double DrawSinOverX::c = 40;
double DrawSinOverX::d = 20;

DrawSinOverX::DrawSinOverX(int _argc, char* _argv[]) :LabBase(_argc, _argv)
{

}

void DrawSinOverX::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_STRIP);
	double sin_x_start = -20;
	double sin_x_end = 20;
	double step = 0.01;
	for (double x = sin_x_start; x < sin_x_end; x += step)
	{
		glVertex2d(a * x + b, c * sin(x) / x + d);
	}
	glEnd();
	glFlush();
}

void DrawSinOverX::on_keyboard(unsigned char key, int x, int y)
{
	if (key == 27/*ESC*/ || key == 'q')
	{
		glutLeaveMainLoop();
	}
	else
	{
		b++;
		display();
	}
}

void DrawSinOverX::init()
{
	glutInit(&argc, argv);
	//glut 初始化 为 rgb颜色模式,单缓冲
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//glut窗体创建
	glutInitWindowSize(1200, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("DrawSinOverX");
	// 设置绘制函数
	glutDisplayFunc(display);
	// 设置键盘操作
	glutKeyboardFunc(on_keyboard);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	gluOrtho2D(-300.0, 300.0, -100.0, 100.0);
}

void DrawSinOverX::run()
{
	// 初始化参数
	init();
	// 执行主循环
	glutMainLoop();
}

DrawSinOverX* DrawSinOverX::get_instance(int argc, char* argv[])
{
	if (instances.count(Lab1))
	{
		return dynamic_cast<DrawSinOverX*>(instances[Lab1]);
	}
	auto instance = new DrawSinOverX(argc, argv);
	instances[Lab1] = instance;
	return instance;
}

DrawSinOverX::~DrawSinOverX()
{
	instances.erase(Lab1);
}
