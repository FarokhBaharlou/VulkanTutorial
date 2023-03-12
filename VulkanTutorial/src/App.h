#pragma once

#include "Window.h"
#include "Pipeline.h"
#include "Device.h"
#include "SwapChain.h"
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
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void freeCommandBuffers();
		void drawFrame();
		void recreateSwapChain();
		void recordCommandBuffer(int imageIndex);
		void renderGameObjects(VkCommandBuffer commandBuffer);
	public:
		static constexpr uint32_t WIDTH = 800;
		static constexpr uint32_t HEIGHT = 600;
	private:
		Window window{ WIDTH, HEIGHT, "Vulkan" };
		Device device{ window };
		std::unique_ptr<SwapChain> swapChain;
		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
		std::vector<GameObject> gameObjects;
	};
}