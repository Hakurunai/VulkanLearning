#ifndef FIRSTAPP__H
#define FIRSTAPP__H

#include "../Windows/LightBoltWindow.hpp"
#include "../LB_pipeline.hpp"

namespace LB
{
	class FirstApp
	{
	public :
		static constexpr int Width{ 800 };
		static constexpr int Height{ 600 };

		void Run();

	private :
		LBWindow lbWindow{ Width, Height, "Vulkan" }; 
		LBPipeline lbPipeline{"../Ressources/Shaders/simple_shader.vert.spv", "../Ressources/Shaders/simple_shader.frag.spv" };
	};
}

#endif // FIRSTAPP__H