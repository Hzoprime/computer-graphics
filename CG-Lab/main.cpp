#include "header.hpp"
int main(int argn, char* argv[])
{
	string a;
	while (getline(cin, a))
	{
		LabBase* lab = nullptr;
		cout << a << endl;
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
		case 3:
			lab = CSClipper::get_instance(argn, argv);
			dynamic_cast<CSClipper*>(lab)->clip();                      
			break;
		case 4: lab = Animation::get_instance(argn, argv); break;
		case 5: lab = CyrusBeckClipper::get_instance(argn, argv); break;
		case 10: lab = CameraLab::get_instance(argn, argv); break;
		case 11: lab = CameraLab2::get_instance(argn, argv); break;
		case 9:
			lab = MeshLab::get_instance(argn, argv);
			auto mesh = new Mesh();
			mesh->read_mesh("lab9.txt");
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
	return 0;
}

