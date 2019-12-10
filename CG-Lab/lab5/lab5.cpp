#include "lab5.hpp"

CyrusBeckClipper::CyrusBeckClipper(int _argc, char* _argv[]) :LabBase(_argc, _argv), boundary(10), adding_point(1)
{

}

#define randdouble (rand()*1.0/RAND_MAX*2*boundary - boundary)
#define randpoint (Point(randdouble, randdouble))
#define randline (Line(randpoint, randpoint))

void CyrusBeckClipper::get_normal_line()
{
	unsigned int length = polygon_points.size();
	for (int i = 0; i < length; i++)
	{
		const Point& a = polygon_points[i];
		const Point& b = polygon_points[(i + 1) % length];
		const Point& c = polygon_points[(i + 2) % length];
		Vector direction1(b.x - a.x, b.y - a.y);
		Vector direction2(c.x - b.x, c.y - b.y);
		Vector n = cross_product(direction1, cross_product(direction1, direction2));
		n.z = 0;
		polygon_normal_lines.push_back(make_pair(n, a));
	}
}

void CyrusBeckClipper::randomize_line_list()
{
	int n = rand() % 5 + 5;
	for (int i = 0; i < n; i++)
	{
		random_line_list.push_back(randline);
	}
}

void CyrusBeckClipper::clip()
{
	for (auto& line : random_line_list)
	{
		Vector direction(line.end.x - line.start.x, line.end.y - line.start.y);
		double t_in = 0;
		double t_out = 1;
		double numer;
		double denom;
		int in_poly = 1;
		for (auto& normal_line : polygon_normal_lines)
		{
			const auto& p = normal_line.second;
			const auto& n = normal_line.first;

			denom = dot_product(direction, n);
			numer = dot_product(Vector(p.x - line.start.x, p.y - line.start.y), n);

			if (denom < 0)
			{
				t_in = max(t_in, numer / denom);
			}
			else
			{
				t_out = min(t_out, numer / denom);
			}
			if (t_in > t_out)
			{
				in_poly = 0;
				break;
			}
		}
		if (in_poly)
		{
			clipped_line_list.push_back(Line(
				Point(line.start.x + (line.end.x - line.start.x) * t_in, line.start.y + (line.end.y - line.start.y ) * t_in),
				Point(line.start.x + (line.end.x - line.start.x) * t_out, line.start.y + (line.end.y - line.start.y) * t_out)
			));
		}
	}
}

void CyrusBeckClipper::display()
{
	if (!instances.count(Lab5))
	{
		return;
	}
	auto instance = get_instance(0, 0);

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(1, 0, 0);
	for (auto& x : instance->random_line_list)
	{
		x.draw_in_gl();
	}
	glColor3d(0, 1, 1);

	if (instance->adding_point)
	{
		glBegin(GL_POINTS);
	}
	else
	{
		glBegin(GL_LINE_LOOP);
	}
	for (auto& x : instance->polygon_points)
	{
		cout << x << endl;
		glVertex2d(x.x, x.y);
	}
	glEnd();

	glColor3d(0, 0, 1);
	for (auto& x : instance->clipped_line_list)
	{
		x.draw_in_gl();
	}


	glFlush();
}

void CyrusBeckClipper::init()
{
	glutInit(&argc, argv);
	//glut 初始化 为 rgb颜色模式,单缓冲
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//glut窗体创建
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("CyrusBeckClipper");
	// 设置绘制函数
	glutDisplayFunc(display);
	// 设置键盘操作
	glutKeyboardFunc(on_keyboard);
	// 设置鼠标操作
	glutMouseFunc(on_mouse);
	//glutMotionFunc(on_drag);
	//glutPassiveMotionFunc(on_move);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	gluOrtho2D(-boundary, boundary, -boundary, boundary);
}

void CyrusBeckClipper::run()
{
	init();
	glutMainLoop();
}

void CyrusBeckClipper::on_mouse(int button, int state, int x, int y)
{
	auto instance = get_instance(0, 0);
	if (!(instance->adding_point))
	{
		return;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		instance->polygon_points.push_back(Point((1.0 * x - 300) / 30, (1.0 * y - 300) / (-30)));
		cout << "state: " << state << endl;
		cout << "size: " << instance->polygon_points.size() << endl;
	}
}

void CyrusBeckClipper::on_keyboard(unsigned char key, int x, int y)
{
	auto instance = get_instance(0, 0);
	if (key == 'q' || key == 'Q' || key == 27/*ESC*/)
	{
		glutLeaveMainLoop();
	}
	else if (key == 'd' || key == 'D')
	{

	}
	else if (key == 'c' || key == 'C')
	{
		// TODO polygon points-> polygon lines with n vector
		instance->get_normal_line();
		instance->adding_point = 0;
		instance->randomize_line_list();
		instance->clip();
	}
	else if (key == 'r' || key == 'R')
	{
		instance->polygon_normal_lines.clear();
		instance->polygon_points.clear();

		instance->random_line_list.clear();
		instance->clipped_line_list.clear();

		instance->adding_point = 1;
	}
	display();
}

CyrusBeckClipper* CyrusBeckClipper::get_instance(int argc, char* argv[])
{
	if (instances.count(Lab5))
	{
		return dynamic_cast<CyrusBeckClipper*>(instances[Lab5]);
	}
	auto instance = new CyrusBeckClipper(argc, argv);
	instances[Lab5] = instance;
	return instance;
}

CyrusBeckClipper::~CyrusBeckClipper()
{
	instances.erase(Lab5);
}
