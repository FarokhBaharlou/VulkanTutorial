#pragma once

#include "Device.h"
#include "Buffer.h"
#include <memory>
#include <vector>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace MyEngine
{
	class Model
	{
	public:
		struct Vertex
		{
			glm::vec3 position{};
			glm::vec3 color{};
			glm::vec3 normal{};
			glm::vec2 uv{};
			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
			bool operator==(const Vertex& rhs) const
			{
				return position == rhs.position && color == rhs.color && normal == rhs.normal && uv == rhs.uv;
			}
		};
		struct Builder
		{
			std::vector<Vertex> vertices{};
			std::vector<uint32_t> indices{};
			void loadModel(const std::string& filePath);
		};
	public:
		Model(Device& device, const Model::Builder& builder);
		~Model();
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;
		static std::unique_ptr<Model> createModelFromFile(Device& device, const std::string& filePath);
		void bind(VkCommandBuffer commandBuffer);
		void draw(VkCommandBuffer commandBuffer);
	private:
		void createVertexBuffers(const std::vector<Vertex>& vertices);
		void createIndexBuffers(const std::vector<uint32_t>& indices);
	private:
		Device& device;
		std::unique_ptr<Buffer> vertexBuffer;
		uint32_t vertexCount;
		bool hasIndexBuffer{ false };
		std::unique_ptr<Buffer> indexBuffer;
		uint32_t indexCount;
	};
}