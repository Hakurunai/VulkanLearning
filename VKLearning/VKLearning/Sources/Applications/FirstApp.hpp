#ifndef FIRSTAPP__H
#define FIRSTAPP__H

#include "../Windows/LB_window.hpp"
#include "../LB_pipeline.hpp"
#include "../LB_device.hpp"

namespace LB
{
	class FirstApp
	{
	public :
		static constexpr int WIDTH{ 800 };
		static constexpr int HEIGHT{ 600 };

		void Run();

	private :
		LBWindow lbWindow{ WIDTH, HEIGHT, "Vulkan" };
		LBDevice lbDevice{ lbWindow };
		LBPipeline lbPipeline{lbDevice, "../Ressources/Shaders/simple_shader.vert.spv", "../Ressources/Shaders/simple_shader.frag.spv", LBPipeline::DefaultPipelineConfigInfo(WIDTH, HEIGHT)};
	};
}

#endif // FIRSTAPP__H