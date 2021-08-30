#include "ecs/system/movement_system.h"

#include "ecs/ecs.h"

using namespace sita::ecs::system;
using namespace sita::ecs::component;

Movement_System::Movement_System()
	: System(System_Flags::Updateable) {
	requireComponent<Transform>();
	requireComponent<Rigid_Body>();
}

void Movement_System::update(const float& dt) {
	for (auto& entity : m_entities) {
		auto& transform = entity.getComponent<Transform>();
		const auto& rigidBody = entity.getComponent<Rigid_Body>();

		transform.position.x += rigidBody.velocity.x;
		transform.position.y += rigidBody.velocity.y;
	}
}
