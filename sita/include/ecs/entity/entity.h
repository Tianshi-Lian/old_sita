#pragma once

#include "core/types.h"

namespace sita::ecs::entity {
	class Entity_Manager;

	class Entity {
	public:
		u64 id;
		
		Entity(u64 id);
		Entity(const Entity& entity) = default;

		void bind(Entity_Manager* entityManager);

		template <typename T, typename ...Args>
		void addComponent(Args&& ...args) const;

		template <typename T>
		void removeComponent() const;

		template <typename T>
		bool hasComponent() const;

		template <typename T>
		T& getComponent() const;

		Entity& operator =(const Entity& other) = default;

		operator u64() const {
			return id;
		}
		
		bool operator ==(const Entity& other) const {
			return id == other.id;
		}
		bool operator !=(const Entity& other) const {
			return id != other.id;
		}
		bool operator >(const Entity& other) const {
			return id > other.id;
		}
		bool operator <(const Entity& other) const {
			return id < other.id;
		}

	private:
		Entity_Manager* m_entityManager;
	};

	template <typename T, typename ...Args>
	void Entity::addComponent(Args&&... args) const {
		m_entityManager->addComponent<T>(id , std::forward<Args>(args)...);
	}

	template <typename T>
	void Entity::removeComponent() const {
		m_entityManager->removeComponent<T>(id);
	}

	template <typename T>
	bool Entity::hasComponent() const {
		return m_entityManager->hasComponent<T>(id);
	}

	template <typename T>
	T& Entity::getComponent() const {
		return m_entityManager->getComponent<T>(id);
	}
}
