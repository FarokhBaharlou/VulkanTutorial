#pragma once

#include "Model.h"
#include <memory>
#include <glm/gtc/matrix_transform.hpp>

namespace MyEngine
{
	struct TransformComponent
	{
		glm::vec3 translation{};
		glm::vec3 scale{ 1.f, 1.f, 1.f };
		glm::vec3 rotation{};
		glm::mat4 mat4();
		glm::mat3 normalMatrix();
	};
	class GameObject
	{
	public:
		using id_t = unsigned int;
	public:
		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;
		GameObject(GameObject&&) = default;
		GameObject& operator=(GameObject&&) = default;
		static GameObject createGameObject()
		{
			static id_t currentId = 0;
			return GameObject{ currentId++ };
		}
		id_t getId() const { return id; }
	public:
		std::shared_ptr<Model> model{};
		glm::vec3 color{};
		TransformComponent transform{};
	private:
		GameObject(id_t objId) : id{ objId } {}
	private:
		id_t id;
	};
}