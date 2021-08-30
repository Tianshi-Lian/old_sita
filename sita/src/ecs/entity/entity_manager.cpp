#include <utility>

#include "ecs/entity/entity_manager.h"

#include "debug/logger.h"
#include "ecs/system/system_manager.h"

using namespace sita::ecs::entity;

Entity_Manager::Entity_Manager(std::shared_ptr<system::System_Manager> systemManager)
	: m_numEntities(0)
	, m_systemManager(std::move(systemManager)) {
}

Entity Entity_Manager::createEntity() {
	u64 entityId;

	if (m_freeIds.empty()) {
		entityId = ++m_numEntities;

		if (entityId >= m_entitySignatures.size()) {
			m_entitySignatures.resize(1 + entityId);
		}
	}
	else {
		entityId = m_freeIds.front();
		m_freeIds.pop_front();
	}

	Entity entity(entityId);
	entity.bind(this);
	m_entitiesToAdd.insert(entity);

	Log::info("Entity_Manager::createEntity - entity created ID: {}", entityId);

	return entity;
}

void Entity_Manager::destroyEntity(Entity entity) {
	m_entitiesToDestroy.insert(entity);

	Log::info("Entity_Manager::destroyEntity - destroying entity ID: {}", entity);
}

void Entity_Manager::update() {
	for (const auto entity : m_entitiesToAdd) {
		const auto entitySignature = m_entitySignatures[entity];
		m_systemManager->addEntityToSystems(entity, entitySignature);
	}
	m_entitiesToAdd.clear();

	for (auto entity : m_entitiesToDestroy) {
		const auto entitySignature = m_entitySignatures[entity];
		m_systemManager->removeEntityFromSystems(entity, entitySignature);

		m_entitySignatures[entity].reset();
		m_freeIds.push_back(entity);
	}
	m_entitiesToDestroy.clear();
}
