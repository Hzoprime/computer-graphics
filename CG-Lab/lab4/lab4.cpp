#include"lab4.hpp"


Animation::Animation(int _argc, char* _argv[]) :LabBase(_argc, _argv)
{

	poly1.push_back(Point(0.5, 0));
	poly1.push_back(Point(0.5, 1));
	poly1.push_back(Point(1.4, 1));

	poly1.push_back(Point(0.3, 3));
	poly1.push_back(Point(1, 3));
	poly1.push_back(Point(0, 5));

	poly1.push_back(Point(-1, 3));
	poly1.push_back(Point(-0.3, 3));
	poly1.push_back(Point(-1.4, 1));

	poly1.push_back(Point(-0.5, 1));
	poly1.push_back(Point(-0.5, 0));

	//for (int i = 0; i < 10; i++)
	//{
	//	poly2.push_back(Point(rand() % 5, rand() % 5));
	//}
}

void Animation::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	auto instance = get_instance(0, 0);
	glBegin(GL_LINE_LOOP);
	for (auto& p : instance->poly1)
	{
		cout << p << endl;
		glVertex2d(p.x, p.y);
	}

	glEnd();
	//glBegin(GL_LINE_LOOP);
	//for (auto& p : instance->poly2)
	//{
	//	glVertex2d(p.x, p.y);
	//}
	//glEnd();
	glFlush();
}

void Animation::on_keyboard(unsigned char key, int x, int y)
{
	if (key == 27/*ESC*/ || key == 'q')
	{
		glutLeaveMainLoop();
	}
	else
	{
		display();
	}
}

void Animation::init()
{
	glutInit(&argc, argv);
	//glut 初始化 为 rgb颜色模式,单缓冲
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//glut窗体创建
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Animation");
	// 设置绘制函数
	glutDisplayFunc(display);
	// 设置键盘操作
	glutKeyboardFunc(on_keyboard);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
}

void Animation::run()
{
	// 初始化参数
	init();
	// 执行主循环
	glutMainLoop();
}

Animation* Animation::get_instance(int argc, char* argv[])
{
	if (instances.count(Lab4))
	{
		return dynamic_cast<Animation*>(instances[Lab4]);
	}
	auto instance = new Animation(argc, argv);
	instances[Lab4] = instance;
	return instance;
}

Animation::~Animation()
{
	instances.erase(Lab4);
}
