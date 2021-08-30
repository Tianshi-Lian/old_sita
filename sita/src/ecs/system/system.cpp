#include "ecs/system/system.h"

using namespace sita::ecs;
using namespace sita::ecs::system;

System::System(System_Flags systemFlags)
	: m_flags(systemFlags) {
}

void System::addEntity(entity::Entity entity) {
	m_entities.push_back(entity);

	postAddEntity(entity);
}

void System::removeEntity(entity::Entity entity) {
	m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
		[&entity](entity::Entity other) {
			return entity == other;
		}), m_entities.end());
}

void System::update(const float& dt) {
}

void System::render(graphics::Renderer2D& renderer) {
}

#ifdef PS_DEBUG
void System::debugRender(graphics::Renderer2D& renderer) {
}
#endif

const std::vector<entity::Entity>& System::getEntities() const {
	return m_entities;
}

const component::Base_Component::Signature& System::getSignature() const {
	return m_signature;
}

System_Flags System::getFlags() const {
	return m_flags;
}

void System::postAddEntity(entity::Entity& entity) {
}
