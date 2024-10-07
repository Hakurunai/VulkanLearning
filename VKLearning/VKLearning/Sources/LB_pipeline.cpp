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