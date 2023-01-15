#pragma once

#include "Window.h"
#include "Pipeline.h"
#include "Device.h"

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
		Device device{ window };
		Pipeline pipeline{device, Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT), "shaders/simple_vertex_shader.vert.spv", "shaders/simple_fragment_shader.frag.spv" };
	};
}