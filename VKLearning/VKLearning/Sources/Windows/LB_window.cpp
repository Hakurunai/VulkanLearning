#include "LB_window.hpp"

//std
#include <stdexcept>

namespace LB
{
	LBWindow::LBWindow(const int Width, const int Height, const std::string Name) 
		: width(Width), height(Height), windowName(Name)
	{
		InitWindow();
	}

	LBWindow::~LBWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void LBWindow::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface)
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
			throw std::runtime_error("Failed to create window surface");
	}

	void LBWindow::InitWindow()
	{
		glfwInit();

		//do not create an openGL context
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		
		//we want to handle the size in another place
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}
}