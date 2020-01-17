#ifndef LAVA_DEBUG_DISPLAY
#define LAVA_DEBUG_DISPLAY
namespace Lava {
	class Debug {
	public:
		static void LogInfo(const char* msg);
		static void LogWarning(const char* msg);
		static void LogError(const char* msg);
		static void Log(const char* msg);
	};
}
#endif