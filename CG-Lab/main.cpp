#include "header.hpp"
int main(int argn, char* argv[])
{
	auto mesh = new Mesh();
	mesh->read_mesh("lab9.txt");
	auto graph = MeshLab::get_instance(argn, argv);
	mesh->draw_in(graph);
	mesh->save_mesh("save_file.txt");
	graph->run();
}
 