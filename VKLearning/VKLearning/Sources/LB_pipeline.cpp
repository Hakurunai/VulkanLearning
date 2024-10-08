#include "LB_pipeline.hpp"

//std
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace LB
{
	LBPipeline::LBPipeline(LBDevice& device, const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo)
		: lbDevice(device)
	{
		CreateGraphicsPipeline(vertFilePath, fragFilePath, configInfo);
	}

	PipelineConfigInfo LBPipeline::DefaultPipelineConfigInfo(uint32_t width, uint32_t height)
	{
		PipelineConfigInfo configInfo{};

		//how the assembler interpret datas
		configInfo.InputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		configInfo.InputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		configInfo.InputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

		//how to transform gl_position values into output image
		configInfo.Viewport.x = 0.0f;
		configInfo.Viewport.y = 0.0f;
		configInfo.Viewport.width = static_cast<float>(width);
		configInfo.Viewport.height = static_cast<float>(height);
		configInfo.Viewport.minDepth = 0.0f;
		configInfo.Viewport.maxDepth = 1.0f;

		configInfo.Scissor.offset = { 0,0 };
		configInfo.Scissor.extent = { width, height };


		configInfo.ViewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		configInfo.ViewportInfo.viewportCount = 1;
		configInfo.ViewportInfo.pViewports = &configInfo.Viewport;
		configInfo.ViewportInfo.scissorCount = 1;
		configInfo.ViewportInfo.pScissors = &configInfo.Scissor;

		configInfo.RasterizationInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		configInfo.RasterizationInfo.depthClampEnable = VK_FALSE;
		configInfo.RasterizationInfo.rasterizerDiscardEnable = VK_FALSE;
		configInfo.RasterizationInfo.polygonMode = VK_POLYGON_MODE_FILL;
		configInfo.RasterizationInfo.lineWidth = 1.0f;
		configInfo.RasterizationInfo.cullMode = VK_CULL_MODE_NONE;
		configInfo.RasterizationInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
		configInfo.RasterizationInfo.depthBiasEnable = VK_FALSE;
		configInfo.RasterizationInfo.depthBiasConstantFactor = 0.0f;  // Optional
		configInfo.RasterizationInfo.depthBiasClamp = 0.0f;           // Optional
		configInfo.RasterizationInfo.depthBiasSlopeFactor = 0.0f;     // Optional

		configInfo.MultisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		configInfo.MultisampleInfo.sampleShadingEnable = VK_FALSE;
		configInfo.MultisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		configInfo.MultisampleInfo.minSampleShading = 1.0f;           // Optional
		configInfo.MultisampleInfo.pSampleMask = nullptr;             // Optional
		configInfo.MultisampleInfo.alphaToCoverageEnable = VK_FALSE;  // Optional
		configInfo.MultisampleInfo.alphaToOneEnable = VK_FALSE;       // Optional

		configInfo.ColorBlendAttachment.colorWriteMask =
			VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
			VK_COLOR_COMPONENT_A_BIT;
		configInfo.ColorBlendAttachment.blendEnable = VK_FALSE;
		configInfo.ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
		configInfo.ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
		configInfo.ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;              // Optional
		configInfo.ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;   // Optional
		configInfo.ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;  // Optional
		configInfo.ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;              // Optional

		configInfo.ColorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		configInfo.ColorBlendInfo.logicOpEnable = VK_FALSE;
		configInfo.ColorBlendInfo.logicOp = VK_LOGIC_OP_COPY;  // Optional
		configInfo.ColorBlendInfo.attachmentCount = 1;
		configInfo.ColorBlendInfo.pAttachments = &configInfo.ColorBlendAttachment;
		configInfo.ColorBlendInfo.blendConstants[0] = 0.0f;  // Optional
		configInfo.ColorBlendInfo.blendConstants[1] = 0.0f;  // Optional
		configInfo.ColorBlendInfo.blendConstants[2] = 0.0f;  // Optional
		configInfo.ColorBlendInfo.blendConstants[3] = 0.0f;  // Optional

		configInfo.DepthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		configInfo.DepthStencilInfo.depthTestEnable = VK_TRUE;
		configInfo.DepthStencilInfo.depthWriteEnable = VK_TRUE;
		configInfo.DepthStencilInfo.depthCompareOp = VK_COMPARE_OP_LESS;
		configInfo.DepthStencilInfo.depthBoundsTestEnable = VK_FALSE;
		configInfo.DepthStencilInfo.minDepthBounds = 0.0f;  // Optional
		configInfo.DepthStencilInfo.maxDepthBounds = 1.0f;  // Optional
		configInfo.DepthStencilInfo.stencilTestEnable = VK_FALSE;
		configInfo.DepthStencilInfo.front = {};  // Optional
		configInfo.DepthStencilInfo.back = {};   // Optional
		return configInfo;
	}

	std::vector<char> LBPipeline::ReadFile(const std::string& filePath)
	{
		std::fstream file{ filePath,std::ios::in | std::ios::ate | std::ios::binary };
		if (!file.is_open())
			throw std::runtime_error("Failed to open file : " + filePath);

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();
		return buffer;
	}

	void LBPipeline::CreateGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath, const PipelineConfigInfo& configInfo)
	{
		auto vertCode = ReadFile(vertFilePath);
		auto fragCode = ReadFile(fragFilePath);

		std::cout << "Vertex shader code size : " << vertCode.size() << "\n";
		std::cout << "Fragment shader code size : " << fragCode.size() << "\n";
		std::cout.flush();
	}
	void LBPipeline::CreateShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		if (vkCreateShaderModule(lbDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
			throw std::runtime_error("Failed to create shader module");
	}
}