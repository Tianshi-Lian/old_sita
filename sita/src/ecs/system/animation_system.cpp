#include "ecs/system/animation_system.h"

#include "ecs/ecs.h"

using namespace sita::ecs::system;
using namespace sita::ecs::component;

Animation_System::Animation_System()
	: System(System_Flags::Updateable) {
	requireComponent<Sprite>();
	requireComponent<Animation>();
}

void Animation_System::update(const float& dt) {
	for (auto& entity : m_entities) {
		auto& animation = entity.getComponent<Animation>();
		auto& sprite = entity.getComponent<Sprite>();

		animation.currentFrame = ((SDL_GetTicks() - animation.startTime) * animation.frameSpeed / 1000) % animation.frameCount;
		sprite.srcX = animation.currentFrame * sprite.width;
	}
}
