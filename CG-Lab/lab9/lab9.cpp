#include"lab9.hpp"

MeshLab::MeshLab(int argc, char* argv[]) :LabBase(argc, argv), boundary(10)
{
}

void MeshLab::display()
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glColor3d(1, 0, 0);
	glBegin(GL_LINES);

	glVertex3d(0, 0, 0);
	glVertex3d(1, 0, 0);

	glEnd();
	glColor3d(0, 1, 0);

	glBegin(GL_LINES);

	glVertex3d(0, 0, 0);
	glVertex3d(0, 1, 0);


	glEnd();

	glColor3d(0, 0, 1);
	glBegin(GL_LINES);

	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 1);

	glEnd();
	glColor3d(1, 1, 1);

	glutWireCube(2);


	//glOrtho(-boundary, boundary, -boundary, boundary, -boundary, boundary);

	glFlush();
}

void MeshLab::init()
{
	glutInit(&argc, argv);
	//glut 初始化 为 rgb颜色模式,单缓冲
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//glut窗体创建
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MeshLab");
	// 设置绘制函数
	glutDisplayFunc(display);
	// 设置键盘操作
	glutKeyboardFunc(on_keyboard);
	// 设置鼠标操作
	//glutMouseFunc(on_mouse);
	//glutMotionFunc(on_drag);

	//glutPassiveMotionFunc(on_move); 
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glEnable(GL_DEPTH_TEST);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3, 4, 4, 0.0, 0, 1, 0.0, 0, 1);


	//glViewport(-600, -600, 600, 600);
	//glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, 1, 100);


}

void MeshLab::run()
{
	init();
	glutMainLoop();
}

void MeshLab::on_keyboard(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q' || key == 27)
	{
		glutLeaveMainLoop();
	}
}

MeshLab* MeshLab::get_instance(int argc, char* argv[])
{
	if (instances.count(Lab9))
	{
		return dynamic_cast<MeshLab*>(instances[Lab9]);
	}
	auto instance = new MeshLab(argc, argv);
	instances[Lab9] = instance;
	return instance;
}

MeshLab::~MeshLab()
{
	instances.erase(Lab9);
}
