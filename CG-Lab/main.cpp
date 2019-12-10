#include "header.hpp"
int main(int argn, char* argv[])
{
	auto graph = CyrusBeckClipper::get_instance(argn, argv);
	graph->run();
}
