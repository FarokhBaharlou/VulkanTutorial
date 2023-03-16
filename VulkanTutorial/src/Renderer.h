#pragma once

#include "Window.h"
#include "Device.h"
#include "SwapChain.h"
#include <memory>
#include <vector>
#include <cassert>

namespace MyEngine
{
	class Renderer
	{
	public:
		Renderer(Window& window, Device& device);
		~Renderer();
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		VkRenderPass getSwapChainRenderPass() const { return swapChain->getRenderPass(); }
		bool isFrameInProgress() const { return isFrameStarted; }
		VkCommandBuffer getCurrentCommandBuffer() const
		{
			assert(isFrameStarted && "cannot get command buffer when frame not in progress");
			return commandBuffers[currentFrameIndex];
		}
		int getFrameIndex() const
		{
			assert(isFrameStarted && "cannot get frame index when frame not in progress");
			return currentFrameIndex;
		}
		VkCommandBuffer beginFrame();
		void endFrame();
		void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
		void endSwapChainRenderPass(VkCommandBuffer commandBuffer);
	private:
		void createCommandBuffers();
		void freeCommandBuffers();
		void recreateSwapChain();
	private:
		Window& window;
		Device& device;
		std::unique_ptr<SwapChain> swapChain;
		std::vector<VkCommandBuffer> commandBuffers;
		uint32_t currentImageIndex;
		int currentFrameIndex{ 0 };
		bool isFrameStarted{ false };
	};
}