#include <iostream>
#include "Debug.h"
void Lava::Debug::LogInfo(const char* msg) {
	std::cout << "Info:" << msg << std::endl;
}

void Lava::Debug::LogWarning(const char* msg) {
	std::cout << "[!]" << msg << std::endl;
}

void Lava::Debug::LogError(const char* msg) {
	std::cout << "[!]ERROR[!] - " << msg << std::endl;
}

void Lava::Debug::Log(const char* msg)
{
	LogInfo(msg);
}
