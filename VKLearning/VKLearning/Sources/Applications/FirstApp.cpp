#include "FirstApp.hpp"

namespace LB
{
	void FirstApp::Run()
	{
		while (!lbWindow.ShouldClose())
		{
			//keyboard, mouse input...
			glfwPollEvents();
		}
	}
}