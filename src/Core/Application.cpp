#include "Application.h"
#include "../../Gameplay/Demo.h"

namespace Lava {
	void Application::Run() {
		WindowManager manager;
		if (manager.GenerateWindow() == -1)
			return;
		
		Lava::Demo::DemoGameLayer gameCode;
		AudioEngine audio_engine;
		audio_engine.Setup();
		gameCode.Start();
		while (!manager.IsWindowClosed()) {
			gameCode.Update();
			audio_engine.Update();
			manager.UpdateWindow();
		}
		manager.DestroyWindow();
		audio_engine.Disable();
	}
}
