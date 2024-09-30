#ifndef LB_PIPELINE__H
#define LB_PIPELINE__H

#include <string>
#include <vector>
namespace LB
{
	class LBPipeline
	{
	public:
		LBPipeline(const std::string& vertFilePath, const std::string& fragFilePath);

	private:
		static std::vector<char> ReadFile(const std::string& filePath);

		void CreateGraphicsPipeline(const std::string& vertFilePath, const std::string& fragFilePath);
	};
}


#endif // !LB_PIPELINE__H