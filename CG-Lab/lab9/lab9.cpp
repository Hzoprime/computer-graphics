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
	glColor3d(1, 1, 1);

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
	gluLookAt(3, 4, 4, 0.0, 0, 1, 0, 0, 1);



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
	else if(key == 's'|| key == 'S')
	{
		get_instance(0, 0)->mesh->save_mesh("on_keyboard.txt");
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
	file << setiosflags(ios::fixed) << setprecision(10);
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

Mesh get_sphere(const double& r, const int& phi_step, const int& theta_step)
{
	Mesh mesh;

	double phi = 0;
	double delta_phi = pi / phi_step;

	double theta = 0;
	double delta_theta = 2 * pi / theta_step;

	vector<Point> upper, lower;
	vector<int> upper_id, lower_id;

	int vertex_count = 0;

	// north pole
	const auto north_pole = Point(0, 0, r);
	mesh.vertex_list.push_back(north_pole);
	vertex_count++;

	// south pole
	const auto south_pole = Point(0, 0, -r);
	mesh.vertex_list.push_back(south_pole);
	vertex_count++;
	
	cout << "begin for north pole" << endl;

	// those face contain north pole
	for (int j = 0; j < theta_step; j++)
	{
		double sin_phi = sin(phi);
		upper.push_back(Point(r * sin_phi * cos(theta), r * sin_phi * sin(theta), r * cos(phi)));
		upper_id.push_back(vertex_count++);
		theta += delta_theta;
	}

	mesh.vertex_list.insert(mesh.vertex_list.end(), upper.begin(), upper.end());

	for (int k = 0; k < upper.size(); k++)
	{
		Mesh::Face face;

		face.vertex_id_list.push_back(0);
		face.vertex_id_list.push_back(upper_id[k]);
		face.vertex_id_list.push_back(upper_id[(k + 1) % upper.size()]);

		Point b = upper[(k + 1) % upper.size()];
		Point c = upper[k];

		auto n = cross_product(get_diff(c, north_pole), get_diff(b, north_pole));

		face.normal_id_list.push_back(mesh.normal_list.size());
		mesh.normal_list.push_back(n);

		mesh.face_list.push_back(face);
	}

	phi += delta_phi;
	cout << "after all about north pole" << endl;
	// those face contain neither pole
	for (int i = 1; i < phi_step - 1; i++)
	{
		lower.clear();
		lower_id.clear();
		theta = 0;
		for (int j = 0; j < theta_step; j++)
		{
			double sin_phi = sin(phi);
			lower.push_back(Point(r * sin_phi * cos(theta), r * sin_phi * sin(theta), r * cos(phi)));
			lower_id.push_back(vertex_count++);
			theta += delta_theta;
		}


		mesh.vertex_list.insert(mesh.vertex_list.end(), lower.begin(), lower.end());

		for (int k = 0; k < lower.size(); k++)
		{
			Mesh::Face face;

			face.vertex_id_list.push_back(upper_id[k]);
			face.vertex_id_list.push_back(upper_id[(k + 1) % lower.size()]);
			face.vertex_id_list.push_back(lower_id[k]);
			face.vertex_id_list.push_back(lower_id[(k + 1) % lower.size()]);

			Point a = upper[k];
			Point b = upper[(k + 1) % lower.size()];
			Point c = lower[k];

			auto n = cross_product(get_diff(c, a), get_diff(b, a));

			face.normal_id_list.push_back(mesh.normal_list.size());
			mesh.normal_list.push_back(n);

			mesh.face_list.push_back(face);
		}

		upper = lower;
		upper_id = lower_id;
		phi += delta_phi;
	}

	cout << "before south pole" << endl;
	// those face contain south pole
	theta = 0;
	for (int j = 0; j < theta_step; j++)
	{
		double sin_phi = sin(phi);
		lower.push_back(Point(r * sin_phi * cos(theta), r * sin_phi * sin(theta), r * cos(phi)));
		lower_id.push_back(vertex_count++);
		theta += delta_theta;
	}

	mesh.vertex_list.insert(mesh.vertex_list.end(), lower.begin(), lower.end());

	for (int k = 0; k < lower.size(); k++)
	{
		Mesh::Face face;

		face.vertex_id_list.push_back(1);
		face.vertex_id_list.push_back(lower_id[k]);
		face.vertex_id_list.push_back(lower_id[(k + 1) % lower.size()]);

		Point b = lower[(k + 1) % lower.size()];
		Point c = lower[k];

		auto n = cross_product(get_diff(b, south_pole), get_diff(c, south_pole));

		face.normal_id_list.push_back(mesh.normal_list.size());
		mesh.normal_list.push_back(n);

		mesh.face_list.push_back(face);
	}

	return mesh;
}
