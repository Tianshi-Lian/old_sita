#include "ecs/entity/entity.h"

#include "ecs/entity/entity_manager.h"

using namespace sita::ecs::entity;

Entity::Entity(u64 id)
	: id(id)
	, m_entityManager(nullptr) {
}

void Entity::bind(Entity_Manager* entityManager) {
	m_entityManager = entityManager;
}
