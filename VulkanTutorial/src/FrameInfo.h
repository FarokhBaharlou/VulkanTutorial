#pragma once

#include "Camera.h"
#include <vulkan/vulkan.h>
#include "GameObject.h"

namespace MyEngine
{
	struct FrameInfo
	{
		int frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		Camera& camera;
		VkDescriptorSet globalDescriptorSet;
		GameObject::Map& gameObjects;
	};
}