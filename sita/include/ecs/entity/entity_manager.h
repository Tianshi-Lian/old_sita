#pragma once

#include <memory>
#include <set>
#include <vector>

#include "ecs/entity/entity.h"
#include "ecs/component/component.h"

#include "core/pool.h"
#include "debug/logger.h"

namespace sita::ecs::system {
	class System_Manager;
}

namespace sita::ecs::entity {

	class Entity_Manager {
	public:
		Entity_Manager(std::shared_ptr<system::System_Manager> systemManager);

		void update();

		/////// Entities
		Entity createEntity();
		void destroyEntity(u64 entityId);


		/////// Components
		template <typename T, typename ...Args>
		void addComponent(u64 entityId, Args&& ...args);

		template <typename T>
		void removeComponent(u64 entityId);

		template <typename T>
		[[nodiscard]] bool hasComponent(u64 entityId) const;

		template <typename T>
		T& getComponent(u64 entityId);

	private:
		void addEntityToSystems(u64 entityId);

		u64 m_numEntities = 0;

		std::set<u64> m_entitiesToAdd;
		std::set<u64> m_entitiesToDestroy;

		std::shared_ptr<system::System_Manager> m_systemManager;

		// Vector index = component ID || Pool index = entity ID
		std::vector<std::shared_ptr<core::IPool>> m_componentPools;

		// Vector index = component ID
		std::vector<component::Base_Component::Signature> m_entitySignatures;
	};

	/////// Components
	template <typename T, typename ... Args>
	void Entity_Manager::addComponent(u64 entityId, Args&&... args) {
		const auto componentId = component::Component<T>::getId();

		if (componentId >= m_componentPools.size()) {
			m_componentPools.resize(componentId + 1, nullptr);
		}

		if (!m_componentPools[componentId]) {
			auto newPool = std::make_shared<core::Pool<T>>();
			m_componentPools[componentId] = newPool;
		}

		auto componentPool = std::static_pointer_cast<core::Pool<T>>(m_componentPools[componentId]);

		if (entityId >= componentPool->getSize()) {
			componentPool->resize(m_numEntities);
		}

		T component(std::forward<Args>(args)...);

		componentPool->set(entityId, component);

		m_entitySignatures[entityId].set(componentId);
	}

	template <typename T>
	void Entity_Manager::removeComponent(u64 entityId) {
		const auto componentId = component::Component<T>::getId();

		m_entitySignatures[entityId].set(componentId, false);
	}

	template <typename T>
	bool Entity_Manager::hasComponent(u64 entityId) const {
		const auto componentId = component::Component<T>::getId();

		return m_entitySignatures[entityId].test(componentId);
	}

	template <typename T>
	T& Entity_Manager::getComponent(u64 entityId) {
		const auto componentId = component::Component<T>::getId();

		if (m_entitySignatures[entityId].test(componentId)) {
			core::Pool<T> componentPool = m_componentPools[componentId];
			if (componentPool) {
				return componentPool.get(entityId);
			}

			Log::error("Entity_Manager::getComponent - Entity contains component which does not exist in pool! ID: {}", componentId);
			return nullptr;
		}

		return nullptr;
	}

}
