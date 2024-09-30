#include "../Application/FirstApp.hpp"

//std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main()
{
	LB::FirstApp app{};

	try
	{
		app.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS; 
}