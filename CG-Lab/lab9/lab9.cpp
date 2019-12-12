#include"lab9.hpp"

MeshLab::MeshLab(int argc, char* argv[]) :LabBase(argc, argv), boundary(10), mesh(nullptr)
{

}

void MeshLab::set_mesh(Mesh* _mesh)
{
	if (!_mesh)
	{
		return;
	}
	this->mesh = _mesh;
}

void MeshLab::display()
{
	auto instance = get_instance(0, 0);
	auto mesh = instance->mesh;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1, 0, 0);

	for (auto& face : mesh->face_list)
	{
		glBegin(GL_LINE_LOOP);
		for (auto& id : face.vertex_id_list)
		{
			glVertex3d(mesh->vertex_list[id].x, mesh->vertex_list[id].y, mesh->vertex_list[id].z);
		}
		glEnd();
	}
	glBegin(GL_LINES);
	glEnd();
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

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3, 4, 4, 0.0, 0, 1, 0.0, 0, 1);



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

Mesh::Mesh()
{

}

int Mesh::read_mesh(string filename)
{
	int vertex_num, normal_num, face_num;
	ifstream file;
	file.open(filename);
	if (!file.is_open() || file.eof())
	{
		cerr << "can not open this file." << endl;
		return 1;
	}
	file >> vertex_num >> normal_num >> face_num;
	vertex_list.resize(vertex_num);
	for (auto& point : vertex_list)
	{
		file >> point.x >> point.y >> point.z;
	}
	normal_list.resize(normal_num);
	for (auto& normal : normal_list)
	{
		file >> normal.x >> normal.y >> normal.z;
	}
	face_list.resize(face_num);
	for (auto& face : face_list)
	{
		int face_vertex_num;
		file >> face_vertex_num;
		face.vertex_id_list.resize(face_vertex_num);
		face.normal_id_list.resize(face_vertex_num);
		for (int j = 0; j < face_vertex_num; j++)
		{
			file >> face.vertex_id_list[j];
		}
		for (int j = 0; j < face_vertex_num; j++)
		{
			file >> face.normal_id_list[j];
		}
	}
	return 0;
}

int Mesh::save_mesh(string filename)
{
	ofstream file(filename);
	if (!file.is_open() || file.eof())
	{
		cerr << "can not open this file." << endl;
		return 1;
	}
	file << vertex_list.size() << ' '
		<< normal_list.size() << ' '
		<< face_list.size()
		<< endl;



	for (auto& point : vertex_list)
	{
		file << point << endl;
	}

	for (auto& normal : normal_list)
	{
		file << normal << endl;
	}

	for (auto& face : face_list)
	{
		file << face << endl;
	}
	file.close();
	return 0;
}

void Mesh::draw_in(MeshLab * mesh_lab)
{
	mesh_lab->set_mesh(this);
}
