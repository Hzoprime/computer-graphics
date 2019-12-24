#pragma once
#include "../ulti.hpp"

class Mesh;

class MeshLab : public LabBase
{
protected:
	MeshLab(int argc, char* argv[]);
	double boundary;
	Mesh* mesh;
public:
	void set_mesh(Mesh* mesh);
	static void display();
	void init();
	void run();
	//static void on_mouse(int button, int state, int x, int y);
	static void on_keyboard(unsigned char key, int x, int y);
	static MeshLab* get_instance(int argc, char* argv[]);
	~MeshLab();
};

class Mesh
{
protected:
public:
	class Face
	{
	public:
		vector<int> vertex_id_list;
		vector<int> normal_id_list;
		friend ostream& operator<< (ostream& out, const Face& f)
		{
			out << f.vertex_id_list.size();
			for (auto& vertex_id : f.vertex_id_list)
			{
				out << ' ' << vertex_id;
			}
			for (auto& normal_id : f.normal_id_list)
			{
				out << ' ' << normal_id;
			}
			return out;
		}
	};

	vector<Point> vertex_list;
	vector<Vector> normal_list;
	vector<Face> face_list;
	Mesh();
	int read_mesh(string filename);
	int save_mesh(string filename);
	void draw_in(MeshLab* mesh_lab);
};


Mesh get_sphere(const double& semidiameter);
