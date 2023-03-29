#pragma once

#include "Pipeline.h"
#include "Device.h"
#include "GameObject.h"
#include "Camera.h"
#include "FrameInfo.h"
#include <memory>
#include <vector>

namespace MyEngine
{
	class RenderSystem
	{
	public:
		RenderSystem(Device& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
		~RenderSystem();
		RenderSystem(const RenderSystem&) = delete;
		RenderSystem& operator=(const RenderSystem&) = delete;
		void renderGameObjects(FrameInfo& frameInfo);
	private:
		void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
		void createPipeline(VkRenderPass renderPass);
	private:
		Device& device;
		std::unique_ptr<Pipeline> pipeline;
		VkPipelineLayout pipelineLayout;
	};
}