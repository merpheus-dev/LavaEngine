#include "TextUtils.h"
#include "Debug.h"
#include <fstream>
#include <sstream>
std::string Lava::TextUtils::ReadText(const char* fileLocation)
{
	std::ifstream fileStream;
	fileStream.open(fileLocation, std::ifstream::in);
	if (!fileStream)
		Debug::Log("Error Opening file " + *fileLocation);

	std::stringstream stringStream;
	stringStream << fileStream.rdbuf();
	std::string content = stringStream.str();
	return content;
}

