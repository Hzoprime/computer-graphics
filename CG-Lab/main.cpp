#include "header.hpp"
int main(int argn, char* argv[])
{
	auto graph = CameraLab::get_instance(argn, argv);
	graph->run();
}

 