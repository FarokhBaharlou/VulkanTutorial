#pragma once

#include "Window.h"
#include "Device.h"
#include "Renderer.h"
#include "GameObject.h"
#include <memory>
#include <vector>

namespace MyEngine
{
	class App
	{
	public:
		App();
		~App();
		App(const App&) = delete;
		App& operator=(const App&) = delete;
		void run();
	private:
		void loadGameObjects();
	public:
		static constexpr uint32_t WIDTH = 800;
		static constexpr uint32_t HEIGHT = 600;
	private:
		Window window{ WIDTH, HEIGHT, "Vulkan" };
		Device device{ window };
		Renderer renderer{ window, device };
		std::vector<GameObject> gameObjects;
	};
}