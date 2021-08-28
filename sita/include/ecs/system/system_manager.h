#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "system.h"

namespace sita::ecs::system {

	class System_Manager {
	public:

		void addEntityToSystems(u64 entityId, component::Base_Component::Signature signature);

		void update();
		void render();

		template <typename T, typename ...Args>
		void addSystem(Args&& ...args);

		template <typename T>
		void removeSystem();

		template <typename T>
		[[nodiscard]] bool hasSystem() const;

		template <typename T>
		System& getSystem();

	private:
		std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems;
	};

	template <typename T, typename ... Args>
	void System_Manager::addSystem(Args&&... args) {
		auto newSystem = std::make_shared<T>(std::forward<Args>(args)...);
		m_systems.insert(std::pair(std::type_index(typeid(T)), newSystem));
	}

	template <typename T>
	void System_Manager::removeSystem() {
		const auto system = m_systems.find(std::type_index(typeid(T)));
		m_systems.erase(system);
	}

	template <typename T>
	bool System_Manager::hasSystem() const {
		const auto system = m_systems.find(std::type_index(typeid(T)));
		return system != m_systems.end();
	}

	template <typename T>
	System& System_Manager::getSystem() {
		const auto system = m_systems.find(std::type_index(typeid(T)));
		return *system->second;
	}

}
