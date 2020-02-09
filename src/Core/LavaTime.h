#pragma once
#include <chrono>
#include <iostream>
namespace Lava {
	class Time {
	public:
		static float deltaTime;
		static float timeScale;
		static void CalculateDeltaTime() {
			long currentTime = std::chrono::duration_cast<std::chrono::milliseconds>
				(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
			deltaTime = ((currentTime - lastTime) / 1000.0) * timeScale;
			lastTime = currentTime;
		}

	private:
		static long lastTime;
	};
}