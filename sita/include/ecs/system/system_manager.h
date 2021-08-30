#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "system.h"
#include "graphics/renderer2d.h"

namespace sita::ecs::system {

	class System_Manager {
	public:

		void addEntityToSystems(entity::Entity entity, component::Base_Component::Signature signature);
		void removeEntityFromSystems(entity::Entity entity, component::Base_Component::Signature signature);

		void update(const float& dt);
		void render(graphics::Renderer2D& renderer);

		template <typename T, typename ...Args>
		void addSystem(Args&& ...args);

		template <typename T>
		void removeSystem();

		template <typename T>
		[[nodiscard]] bool hasSystem() const;

		template <typename T>
		std::shared_ptr<T> getSystem();

	private:
		std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems;
		std::unordered_map<std::type_index, std::shared_ptr<System>> m_updateSystems;
		std::unordered_map<std::type_index, std::shared_ptr<System>> m_renderSystems;
	};

	template <typename T, typename ... Args>
	void System_Manager::addSystem(Args&&... args) {
		auto newSystem = std::make_shared<T>(std::forward<Args>(args)...);
		m_systems.insert(std::pair(std::type_index(typeid(T)), newSystem));

		System_Flags flags = newSystem->getFlags();
		if (flags & System_Flags::Updateable) {
			m_updateSystems.insert(std::pair(std::type_index(typeid(T)), newSystem));
		}
		if (flags & System_Flags::Renderable) {
			m_renderSystems.insert(std::pair(std::type_index(typeid(T)), newSystem));
		}
	}

	template <typename T>
	void System_Manager::removeSystem() {
		const auto system = m_systems.find(std::type_index(typeid(T)));

		System_Flags flags = system->second->getFlags();
		if (flags & System_Flags::Updateable) {
			const auto updateSystem = m_updateSystems.find(std::type_index(typeid(T)));
			m_updateSystems.erase(updateSystem);
		}
		if (flags & System_Flags::Renderable) {
			const auto renderSystem = m_renderSystems.find(std::type_index(typeid(T)));
			m_renderSystems.erase(renderSystem);
		}

		m_systems.erase(system);
	}

	template <typename T>
	bool System_Manager::hasSystem() const {
		const auto system = m_systems.find(std::type_index(typeid(T)));
		return system != m_systems.end();
	}

	template <typename T>
	std::shared_ptr<T> System_Manager::getSystem() {
		const auto system = m_systems.find(std::type_index(typeid(T)));
		return std::static_pointer_cast<T>(system->second);
	}

}
