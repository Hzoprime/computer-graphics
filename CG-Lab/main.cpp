#include "header.hpp"
int main(int argn, char* argv[])
{
	auto graph = CSClipper::get_instance(argn, argv);
	graph->run();
}