#pragma once

#include <deque>
#include <memory>
#include <set>
#include <vector>

#include "ecs/entity/entity.h"
#include "ecs/component/component.h"

#include "core/pool.h"

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
		void destroyEntity(Entity entity);


		/////// Components
		template <typename T, typename ...Args>
		void addComponent(Entity entity, Args&& ...args);

		template <typename T>
		void removeComponent(Entity entityId);

		template <typename T>
		[[nodiscard]] bool hasComponent(u64 entityId) const;

		template <typename T>
		T& getComponent(Entity entityId);

	private:
		u64 m_numEntities;

		std::deque<u64> m_freeIds;

		std::set<Entity> m_entitiesToAdd;
		std::set<Entity> m_entitiesToDestroy;

		std::shared_ptr<system::System_Manager> m_systemManager;

		// Vector index = component ID || Pool index = entity ID
		std::vector<std::shared_ptr<core::IPool>> m_componentPools;

		// Vector index = component ID
		std::vector<component::Base_Component::Signature> m_entitySignatures;
	};

	/////// Components
	template <typename T, typename ... Args>
	void Entity_Manager::addComponent(Entity entity, Args&&... args) {
		const auto componentId = component::Component<T>::getId();

		if (componentId >= m_componentPools.size()) {
			m_componentPools.resize(componentId + 1, nullptr);
		}

		if (!m_componentPools[componentId]) {
			auto newPool = std::make_shared<core::Pool<T>>();
			m_componentPools[componentId] = newPool;
		}

		auto componentPool = std::static_pointer_cast<core::Pool<T>>(m_componentPools[componentId]);

		if (entity >= componentPool->getSize()) {
			componentPool->resize(m_numEntities * 2);
		}

		T component(std::forward<Args>(args)...);

		componentPool->set(entity, component);

		m_entitySignatures[entity].set(componentId);
	}

	template <typename T>
	void Entity_Manager::removeComponent(Entity entity) {
		const auto componentId = component::Component<T>::getId();

		m_entitySignatures[entity].set(componentId, false);
	}

	template <typename T>
	bool Entity_Manager::hasComponent(u64 entity) const {
		const auto componentId = component::Component<T>::getId();

		return m_entitySignatures[entity].test(componentId);
	}

	template <typename T>
	T& Entity_Manager::getComponent(Entity entity) {
		const auto componentId = component::Component<T>::getId();

		auto componentPool = std::static_pointer_cast<core::Pool<T>>(m_componentPools[componentId]);
		return componentPool->get(entity);
	}

}
