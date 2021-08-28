#include <utility>

#include "ecs/entity/entity_manager.h"

#include "debug/logger.h"
#include "ecs/system/system_manager.h"

using namespace sita::ecs::entity;

Entity_Manager::Entity_Manager(std::shared_ptr<system::System_Manager> systemManager)
	: m_systemManager(std::move(systemManager)) {
}

Entity Entity_Manager::createEntity() {
	const u64 entityId = m_numEntities++;

	if (entityId >= m_entitySignatures.size()) {
		m_entitySignatures.resize(1 + entityId);
	}

	Entity entity(entityId);
	m_entitiesToAdd.insert(entityId);

	entity.bind(this);

	Log::info("Entity_Manager::createEntity - entity created ID: {}", entityId);

	return entity;
}

void Entity_Manager::destroyEntity(u64 entityId) {
}

void Entity_Manager::addEntityToSystems(u64 entityId) {
	const auto entitySignature = m_entitySignatures[entityId];
	m_systemManager->addEntityToSystems(entityId, entitySignature);
}

void Entity_Manager::update() {
	for (const auto entity : m_entitiesToAdd) {
		addEntityToSystems(entity);
	}
	m_entitiesToAdd.clear();
}
