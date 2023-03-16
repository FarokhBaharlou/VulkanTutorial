#include "App.h"
#include "RenderSystem.h"
#include <stdexcept>
#include <array>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace MyEngine
{
	App::App()
	{
		loadGameObjects();
	}
	App::~App() {}
	void App::run()
	{
		RenderSystem renderSystem{ device, renderer.getSwapChainRenderPass() };
		while (!window.shouldClose())
		{
			glfwPollEvents();
			if (auto commandBuffer = renderer.beginFrame())
			{
				renderer.beginSwapChainRenderPass(commandBuffer);
				renderSystem.renderGameObjects(commandBuffer, gameObjects);
				renderer.endSwapChainRenderPass(commandBuffer);
				renderer.endFrame();
			}
		}
		vkDeviceWaitIdle(device.device());
	}
	void App::loadGameObjects()
	{
		std::vector<Model::Vertex> vertices{ {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}}, {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}}, {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}} };
		auto model = std::make_shared<Model>(device, vertices);

		auto triangle = GameObject::createGameObject();
		triangle.model = model;
		triangle.color = { .1f, .8f, .1f };
		triangle.transform2d.translation.x = .2f;
		triangle.transform2d.scale = { 2.f, .5f };
		triangle.transform2d.rotation = .25f * glm::two_pi<float>();
		gameObjects.push_back(std::move(triangle));
	}
}