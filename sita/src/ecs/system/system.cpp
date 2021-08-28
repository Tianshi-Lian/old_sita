#include "ecs/system/system.h"

using namespace sita::ecs;
using namespace sita::ecs::system;

void System::addEntity(u64 entityId) {
	m_entities.push_back(entityId);
}

void System::removeEntity(u64 entityId) {
	m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
		[&entityId](u64 other) {
			return entityId == other;
		}), m_entities.end());
}

const std::vector<u64>& System::getEntities() const {
	return m_entities;
}

const component::Base_Component::Signature& System::getSignature() const {
	return m_signature;
}
