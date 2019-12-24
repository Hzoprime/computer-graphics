#include "header.hpp"
int main(int argn, char* argv[])
{
	string a;
	Mesh sphere = get_sphere(2, 20, 20);
	while (getline(cin, a))
	{
		if (a == "q")
			break;
		LabBase* lab = nullptr;
		stringstream ss;
		ss.clear();
		ss << a;
		int b;
		ss >> b;
		switch (b)
		{
		default:
			break;
		case 1:	lab = DrawSinOverX::get_instance(argn, argv); break;
		case 2: lab = PolyLineApp::get_instance(argn, argv); break;
		case 3: lab = CSClipper::get_instance(argn, argv); break;
		case 4: lab = Animation::get_instance(argn, argv); break;
		case 5: lab = CyrusBeckClipper::get_instance(argn, argv); break;
		case 10: lab = CameraLab::get_instance(argn, argv); break;
		case 11: lab = CameraLab2::get_instance(argn, argv); break;
		case 91:
			lab = MeshLab::get_instance(argn, argv);
			dynamic_cast<MeshLab*>(lab)->set_mesh(&sphere);
			break;
		case 9:
			lab = MeshLab::get_instance(argn, argv);
			auto mesh = new Mesh();
			mesh->read_mesh("on_keyboard.txt");
			dynamic_cast<MeshLab*>(lab)->set_mesh(mesh);
			break;
		}
		if (!lab)
		{
			break;
		}
		lab->run();
		delete lab;
	}
	cout << "lab" << endl;
	return 0;
}

