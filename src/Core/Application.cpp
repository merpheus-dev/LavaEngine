#include "Application.h"
#include "../Core/AudioEngine.h"
#include "../../Gameplay/Demo.h"

namespace Lava {
	void Application::Run() {
		WindowManager manager;
		if (manager.GenerateWindow() == -1)
			return;

		auto gameCode = new Lava::Demo::DemoGameLayer();
		AudioEngine audio_engine;
		audio_engine.Setup();
		gameCode->Start();
		while (!manager.IsWindowClosed()) {
			gameCode->Update();
			audio_engine.Update();
			manager.UpdateWindow();
		}
		audio_engine.Disable();
		manager.DestroyWindow();
	}
}
