#include "ecs/system/system_manager.h"

using namespace sita::ecs::system;

void System_Manager::addEntityToSystems(u64 entityId, component::Base_Component::Signature signature) {
	for (const auto& system : m_systems) {
		const auto systemSignature = system.second->getSignature();

		const bool signatureMatch = (signature & systemSignature) == systemSignature;
		if (signatureMatch) {
			system.second->addEntity(entityId);
		}
	}
}

void System_Manager::update() {
	//for (const auto& system : m_systems) {
	//	system.second->update();
	//}
}

void System_Manager::render() {
}
