#include "ecs/system/system_manager.h"

using namespace sita::ecs::system;

void System_Manager::addEntityToSystems(entity::Entity entity, component::Base_Component::Signature signature) {
	for (const auto& system : m_systems) {
		const auto systemSignature = system.second->getSignature();

		const bool signatureMatch = (signature & systemSignature) == systemSignature;
		if (signatureMatch) {
			system.second->addEntity(entity);
		}
	}
}

void System_Manager::removeEntityFromSystems(entity::Entity entity, component::Base_Component::Signature signature) {
	for (const auto& system : m_systems) {
		const auto systemSignature = system.second->getSignature();

		const bool signatureMatch = (signature & systemSignature) == systemSignature;
		if (signatureMatch) {
			system.second->removeEntity(entity);
		}
	}
}

void System_Manager::update(const float& dt) {
	for (const auto& system : m_updateSystems) {
		system.second->update(dt);
	}
}

void System_Manager::render(graphics::Renderer2D& renderer) {
	for (const auto& system : m_renderSystems) {
		system.second->render(renderer);
	}

#ifdef PS_DEBUG
	for (const auto& system : m_renderSystems) {
		system.second->debugRender(renderer);
	}
#endif

}
