#include"lab2.hpp"
char PolyLineApp::status;
double distance(const Point& a, const Point& b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}
PolyLineApp::PolyLineApp(int argc, char* argv[]) : LabBase(argc, argv), dragged_point(nullptr), moving_point(nullptr)
{

}

void PolyLineApp::display()
{
	if (!instances.count(Lab2))
	{
		return;
	}
	auto instance = dynamic_cast<PolyLineApp*>(instances[Lab2]);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto& polyline : instance->polylines)
	{
		glBegin(GL_LINE_STRIP);
		for (auto& point : polyline)
		{
			glVertex2d(point.x, instance->height - point.y);
		}
		glEnd();
	}

	for (auto& polygon : instance->polygons)
	{
		glBegin(GL_LINE_LOOP);
		for (auto& point : polygon)
		{
			glVertex2d(point.x, instance->height - point.y);
		}
		glEnd();
	}
	glFlush();
}

void PolyLineApp::on_keyboard(unsigned char key, int x, int y)
{
	if (!instances.count(Lab2))
	{
		return;
	}
	if (key == 'q' || key == 'Q')
	{
		glutLeaveMainLoop();
	}
	auto instance = dynamic_cast<PolyLineApp*>(instances[Lab2]);
	cout << "on_keyboard with input: " << key << endl;
	status = key;
	if (status == 'b' || status == 'B')
	{
		instance->polylines.push_back(Polyline());
	}
	if (status == 'r' || status == 'R')
	{
		if (instance->polylines.size())
		{
			if (instance->polylines.back().size() > 1)
			{
				cout << instance->polylines.back()[instance->polylines.back().size() - 1] << endl << instance->polylines.back()[instance->polylines.back().size() - 2]<< endl;
				instance->polylines.back().pop_back();
			}
		}
		display();
	}
	cout << "key = " << key << endl;
}
#define DEBUG
void PolyLineApp::on_mouse(int button, int state, int x, int y)
{
	if (!instances.count(Lab2))
	{
		return;
	}
	auto instance = dynamic_cast<PolyLineApp*>(instances[Lab2]);
#ifdef DEBUG
	cout << "status: " << status << endl;
#endif // DEBUG
	Point point(x, y);
	switch (status)
	{
	default:
		break;
	case 'b':
	case 'B':
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (instance->polylines.back().size())
			{
				instance->polylines.back().pop_back();
			}
			instance->add_point(point);
			instance->add_point(point);
		}
		break;
	case 'd':
	case 'D':
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			instance->delete_point(point);
		}
		break;
	case 'm':
	case 'M':
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			instance->dragged_point = instance->get_near_point(point);
		}
		break;
	}
	display();
}

void PolyLineApp::on_drag(int x, int y)
{
	auto instance = dynamic_cast<PolyLineApp*>(instances[Lab2]);
	if ((instance->status == 'm' || instance->status == 'M') && instance->dragged_point)
	{
		instance->dragged_point->x = x;
		instance->dragged_point->y = y;
	}
	display();
}

void PolyLineApp::on_move(int x, int y)
{
	auto instance = dynamic_cast<PolyLineApp*>(instances[Lab2]);
	if ((instance->status == 'b' || instance->status == 'B') && instance->polylines.back().size())
	{
		instance->polylines.back().back().x = x;
		instance->polylines.back().back().y = y;
	}
	display();
}

void PolyLineApp::init()
{
	glutInit(&argc, argv);
	//glut 初始化 为 rgb颜色模式,单缓冲
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//glut窗体创建
	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("PolyLineApp");
	// 设置绘制函数
	glutDisplayFunc(display);
	// 设置键盘操作
	glutKeyboardFunc(on_keyboard);
	// 设置鼠标操作
	glutMouseFunc(on_mouse);
	glutMotionFunc(on_drag);
	glutPassiveMotionFunc(on_move);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	gluOrtho2D(0, width, 0, height);
}

void PolyLineApp::run()
{
	init();
	glutMainLoop();
}

Point PolyLineApp::near_to(double x, double y)
{
	Point temp(x, y);
	return temp;
}

Point PolyLineApp::get_new_point(double x, double y)
{
	Point temp(x, y);
	auto start = dynamic_cast<PolyLineApp*>(instances[Lab2])->polylines.back().front();
	if (distance(start, temp) < 10)
	{
		return start;
	}
	return temp;
}

void PolyLineApp::add_point(const Point& point)
{
	if (!status)
	{
		return;
	}
	auto instance = dynamic_cast<PolyLineApp*>(instances[Lab2]);
	instance->polylines.back().push_back(point);
	if (instance->polylines.back().size() > 2 && distance(instance->polylines.back().back(), instance->polylines.back().front()) < 10)
	{
		status = 0;
		instance->polylines.back().pop_back();
		instance->polygons.push_back(instance->polylines.back());
		instance->polylines.pop_back();
	}
}

void PolyLineApp::delete_point(const Point& point)
{
	auto instance = dynamic_cast<PolyLineApp*>(instances[Lab2]);
	for (auto& polyline : instance->polylines)
	{
		for (auto it = polyline.begin(); it != polyline.end(); it++)
		{
			if (distance(*it, point) < 10)
			{
				polyline.erase(it);
				return;
			}
		}
	}
	for (auto& polygon : instance->polygons)
	{
		for (auto it = polygon.begin(); it != polygon.end(); it++)
		{
			if (distance(*it, point) < 10)
			{
				polygon.erase(it);
				return;
			}
		}
	}
}

Point* PolyLineApp::get_near_point(const Point& point)
{
	auto instance = dynamic_cast<PolyLineApp*>(instances[Lab2]);
	for (auto& polyline : instance->polylines)
	{
		for (auto it = polyline.begin(); it != polyline.end(); it++)
		{
			if (distance(*it, point) < 10)
			{
				return &(*it);
			}
		}
	}
	for (auto& polygon : instance->polygons)
	{
		for (auto it = polygon.begin(); it != polygon.end(); it++)
		{
			if (distance(*it, point) < 10)
			{
				return &(*it);
			}
		}
	}
	return nullptr;
}

PolyLineApp* PolyLineApp::get_instance(int argc, char* argv[])
{
	if (instances.count(Lab2))
	{
		return dynamic_cast<PolyLineApp*>(instances[Lab2]);
	}
	auto instance = new PolyLineApp(argc, argv);
	instances[Lab2] = instance;
	return instance;
}

PolyLineApp::~PolyLineApp()
{
	instances.erase(Lab2);
}

