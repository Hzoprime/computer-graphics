#include"lab4.hpp"


Animation::Animation(int _argc, char* _argv[]) :LabBase(_argc, _argv)
{
	direction = 1;
	is_pause = 0;
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




	poly2.push_back(Point(-0.25, 0));
	poly2.push_back(Point(0.75, 0));
	poly2.push_back(Point(0.75, 1));

	poly2.push_back(Point(1.75, 1));
	poly2.push_back(Point(1.75, 2));
	poly2.push_back(Point(0.75, 2));

	poly2.push_back(Point(0.75, 3));
	poly2.push_back(Point(1.75, 3));
	poly2.push_back(Point(1.75, 4));
	poly2.push_back(Point(0.75, 4));
	poly2.push_back(Point(-0.25, 4));

	poly3.resize(poly1.size());
}

void Animation::display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	auto instance = get_instance(0, 0);
	//glBegin(GL_LINE_LOOP);
	//for (auto& p : instance->poly1)
	//{
	//	glVertex2d(p.x, p.y);
	//}

	//glEnd();
	glBegin(GL_LINE_LOOP);
	for (auto& p : instance->poly3)
	{
		glVertex2d(p.x, p.y);
	}
	glEnd();
	glFlush();
}

void Animation::on_keyboard(unsigned char key, int x, int y)
{
	if (key == 27/*ESC*/ || key == 'q')
	{
		glutLeaveMainLoop();
	}
	else if (key == 'p' || key == 'P')
	{
		get_instance(0, 0)->is_pause = 1;
	}
	else
	{
		get_instance(0, 0)->is_pause = 0;
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
	//glutIdleFunc(animation);
	glutTimerFunc(10, animation, 0);
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


//void Animation::animation()
//{
//	int times = 100;
//	auto instance = get_instance(0, 0);
//	for (int i = 0; i < times; i++)
//	{
//		for (int j = 0; j < instance->poly1.size(); j++)
//		{
//			instance->interpolate(times, i);
//		}
//	}
//	for (int i = times; i >= 0; i--)
//	{
//		for (int j = 0; j < instance->poly1.size(); j++)
//		{
//			instance->interpolate(times, i);
//		}
//	}
//}

void Animation::animation(int value)
{
	int times = 1000;
	auto instance = get_instance(0, 0);
	if ((value >= times && instance->direction) || (value <= 0 && !(instance->direction)))
	{
		instance->direction = !(instance->direction);
	}
	instance->interpolate(times, value);
	if (instance->is_pause)
	{
		glutTimerFunc(10, animation, value);
	}
	else if (instance->direction)
	{
		glutTimerFunc(10, animation, value + 1);
	}
	else
	{
		glutTimerFunc(10, animation, value - 1);
	}
}

void Animation::interpolate(const int& n, const int& t)
{
	for (int i = 0; i < poly1.size(); i++)
	{
		poly3[i] = (1 - 1.0 * t / n) * poly1[i] + (1.0 * t / n) * poly2[i];
	}
	display();
}
Animation * Animation::get_instance(int argc, char* argv[])
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
