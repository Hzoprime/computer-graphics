#include"lab3.hpp"



void CSClipper::display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	auto instance = get_instance(0, 0);
	instance->rect.draw_in_gl();

	cout << instance->clipped_lines.size() << endl;

	for (const auto& line : instance->clipped_lines)
	{
		line.draw_in_gl();
		cout << line << endl;
	}

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
	gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
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

void CSClipper::on_keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	default:
		break;
	case 'q':
	case 'Q':
	case 27:
		glutLeaveMainLoop();
	}
}

void CSClipper::clip()
{
	const Point& rect_point_1 = this->rect.points[0];
	const Point& rect_point_2 = this->rect.points[2];
	double boundary[4];
	boundary[0] = min(rect_point_1.x, rect_point_2.x); // left
	boundary[1] = max(rect_point_1.x, rect_point_2.x); // right
	boundary[2] = min(rect_point_1.y, rect_point_2.y); // top
	boundary[3] = max(rect_point_1.y, rect_point_2.y); // botton
	for (const auto& line : raw_lines)
	{
		auto temp_line(line);
		auto& start = temp_line.start;
		auto& end = temp_line.end;
		while (true)
		{
			int start_code = code_point(start, boundary);
			int end_code = code_point(end, boundary);
			int code = start_code | end_code;

			if (!code)
			{
				clipped_lines.push_back(temp_line);
				break;
			}
			else if (start_code & end_code)
			{
				break;
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					if (code & codes[i])
					{
						Point intersection;
						if (i < 2)
						{
							double y = (boundary[i] - start.x) * (end.y - start.y) / (end.x - start.x) + start.y;
							intersection.x = boundary[i];
							intersection.y = y;
						}
						else
						{
							double x = (boundary[i] - start.y) * (end.x - start.x) / (end.y - start.y) + start.x;
							intersection.x = x;
							intersection.y = boundary[i];
						}

						if (start_code & codes[i])
						{
							start = intersection;
						}
						else
						{
							end = intersection;
						}
						break;
					}
				}
			}
		}
	}
}

CSClipper::~CSClipper()
{
	instances.erase(Lab3);
}

int CSClipper::code_point(const Point & point, double boundary[4])
{
	int code = 0;
	if (point.x < boundary[0]) code += 8;
	if (point.x > boundary[1]) code += 4;
	if (point.y < boundary[2]) code += 2;
	if (point.y > boundary[3]) code += 1;
	return code;
}

CSClipper::CSClipper(int argc, char* argv[]) : LabBase(argc, argv), rect(Point(0, 0), Point(6, 6))
{
	raw_lines.push_back(Line(Point(1, 1), Point(2, 4)));
	raw_lines.push_back(Line(Point(2, 1), Point(7, 4)));
	raw_lines.push_back(Line(Point(1, -5), Point(8, -1)));
	raw_lines.push_back(Line(Point(-1, 8), Point(7, -2)));
}
