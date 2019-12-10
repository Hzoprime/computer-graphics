#include "header.hpp"
int main(int argn, char* argv[])
{
	auto graph = MeshLab::get_instance(argn, argv);
	graph->run();
}
 