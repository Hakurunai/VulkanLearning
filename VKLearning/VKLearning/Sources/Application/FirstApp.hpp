#ifndef FIRSTAPP__H
#define FIRSTAPP__H

#include "../Window/LightBoltWindow.hpp"

namespace LB
{
	class FirstApp
	{
	public :
		static constexpr int Width{ 800 };
		static constexpr int Height{ 600 };

		void Run();

	private :
		LBWindow lbWindow{ Width, Height, "Vulkan Powaaa" };
	};
}

#endif // FIRSTAPP__H