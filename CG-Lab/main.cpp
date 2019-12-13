#include "header.hpp"
int main(int argn, char* argv[])
{
	auto graph = CameraLab2::get_instance(argn, argv);
	graph->run();
}

 