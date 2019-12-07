#include "header.hpp"
int main(int argn, char* argv[])
{
	auto graph = Animation::get_instance(argn, argv);
	graph->run();
}
