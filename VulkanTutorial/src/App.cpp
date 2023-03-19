#include "App.h"
#include "RenderSystem.h"
#include "Camera.h"
#include "Controller.h"
#include <stdexcept>
#include <array>
#include <chrono>
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
        Camera camera{};
        camera.setViewTarget(glm::vec3(-1., -2.f, 2.f), glm::vec3(0.f, 0.f, 2.5f));
        auto viewerObject = GameObject::createGameObject();
        Controller cameraController{};
        auto currentTime = std::chrono::high_resolution_clock::now();
		while (!window.shouldClose())
		{
			glfwPollEvents();
            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;
            cameraController.moveInPlaneXZ(window.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);
            float aspect = renderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 10.f);
			if (auto commandBuffer = renderer.beginFrame())
			{
				renderer.beginSwapChainRenderPass(commandBuffer);
				renderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
				renderer.endSwapChainRenderPass(commandBuffer);
				renderer.endFrame();
			}
		}
		vkDeviceWaitIdle(device.device());
	}
	void App::loadGameObjects()
	{
        std::shared_ptr<Model> model = Model::createModelFromFile(device, "models/flat_vase.obj");
        auto flatVase = GameObject::createGameObject();
		flatVase.model = model;
		flatVase.transform.translation = { -.5f, .5f, 2.5f };
		flatVase.transform.scale = { 3.f, 1.5f, 3.f };
        gameObjects.push_back(std::move(flatVase));

		model = Model::createModelFromFile(device, "models/smooth_vase.obj");
		auto smoothVase = GameObject::createGameObject();
		smoothVase.model = model;
		smoothVase.transform.translation = { .5f, .5f, 2.5f };
		smoothVase.transform.scale = { 3.f, 1.5f, 3.f };
		gameObjects.push_back(std::move(smoothVase));
	}
}