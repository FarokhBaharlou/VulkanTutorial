#pragma once

#include "Window.h"

namespace MyEngine
{
	class App
	{
	public:
		void run();
	public:
		static constexpr uint32_t WIDTH = 800;
		static constexpr uint32_t HEIGHT = 600;
	private:
		Window window{ WIDTH, HEIGHT, "Vulkan" };
	};
}