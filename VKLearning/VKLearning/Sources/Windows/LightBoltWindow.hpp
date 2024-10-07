#ifndef LIGHTBOLTWINDOW__H
#define LIGHTBOLTWINDOW__H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace LB
{
	class LBWindow
	{
	public :
#pragma region CTOR
		LBWindow(const int Width, const int Height, const std::string Name);

		LBWindow(const LBWindow& other) = delete;
		LBWindow& operator=(const LBWindow& other) = delete;

		~LBWindow();
#pragma endregion CTOR
		__forceinline bool ShouldClose() const { return glfwWindowShouldClose(window); }

		void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
	private :
		void InitWindow();

		const int width;
		const int height;

		GLFWwindow* window;
		std::string windowName;
	};
}

#endif // LIGHTBOLTWINDOW__H