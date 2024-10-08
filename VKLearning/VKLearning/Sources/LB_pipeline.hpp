#ifndef LB_PIPELINE__H
#define LB_PIPELINE__H

#include "LB_device.hpp"

//std
#include <string>
#include <vector>
namespace LB
{
	struct PipelineConfigInfo 
	{
		VkViewport Viewport;
		VkRect2D Scissor;
		VkPipelineViewportStateCreateInfo ViewportInfo;
		VkPipelineInputAssemblyStateCreateInfo InputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo RasterizationInfo;
		VkPipelineMultisampleStateCreateInfo MultisampleInfo;
		VkPipelineColorBlendAttachmentState ColorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo ColorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo DepthStencilInfo;
		VkPipelineLayout PipelineLayout = nullptr;
		VkRenderPass RenderPass = nullptr;
		uint32_t Subpass = 0;
	};

	class LBPipeline
	{
	public:
#pragma region CTOR
		LBPipeline(LBDevice& device, const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo);
		~LBPipeline(){}

		LBPipeline(const LBPipeline&) = delete;
		void operator=(const LBPipeline&) = delete;
#pragma endregion CTOR

		static PipelineConfigInfo DefaultPipelineConfigInfo(uint32_t width, uint32_t height);
	private:
		static std::vector<char> ReadFile(const std::string& filePath);

		void CreateGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo);

		void CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		//the device should exist to allow a pipeline to be
		LBDevice& lbDevice;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
	};
}
#endif // !LB_PIPELINE__H