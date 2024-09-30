#include "LB_pipeline.hpp"

//std
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace LB
{
	LBPipeline::LBPipeline(const std::string& vertFilePath, const std::string& fragFilePath)
	{
		CreateGraphicsPipeline(vertFilePath, fragFilePath);
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

	void LBPipeline::CreateGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath)
	{
		auto vertCode = ReadFile(vertFilePath);
		auto fragCode = ReadFile(fragFilePath);

		std::cout << "Vertex shader code size : " << vertCode.size() << "\n";
		std::cout << "Fragment shader code size : " << fragCode.size() << "\n";
		std::cout.flush();
	}
}