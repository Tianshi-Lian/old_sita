#include "ecs/system/collision_system.h"

#include "debug/logger.h"
#include "ecs/ecs.h"

using namespace sita::ecs::system;
using namespace sita::ecs::component;

#ifdef PS_DEBUG
Collision_System::Collision_System()
	: System(System_Flags::Updateable | System_Flags::Renderable)
	, m_showBoundingBoxes(false) {
	requireComponent<Transform>();
	requireComponent<Box_Collider>();
}
#else
Collision_System::Collision_System()
	: System(System_Flags::Updateable) {
	requireComponent<Transform>();
	requireComponent<Box_Collider>();
}
#endif

inline bool checkAABBCollision(
	f32 aX, f32 aY, f32 aW, f32 aH,
	f32 bX, f32 bY, f32 bW, f32 bH) {

	return (
		aX < bX + bW &&
		aX + aW > bX &&
		aY < bY + bH &&
		aY + aH > bY);
}

void Collision_System::update(const float& dt) {
	for (auto i = m_entities.begin(); i != m_entities.end(); ++i) {
		entity::Entity& a = *i;
		const auto& aTransform = a.getComponent<Transform>();
		const auto& aCollider = a.getComponent<Box_Collider>();

		for (auto j = i + 1; j != m_entities.end(); ++j) {
			entity::Entity& b = *j;
			const auto& bTransform = b.getComponent<Transform>();
			const auto& bCollider = b.getComponent<Box_Collider>();

			if (checkAABBCollision(
				aTransform.position.x + aCollider.offset.x * aTransform.scale.x,
				aTransform.position.y + aCollider.offset.y * aTransform.scale.y,
				static_cast<f32>(aCollider.width) * aTransform.scale.x,
				static_cast<f32>(aCollider.height) * aTransform.scale.y,
				bTransform.position.x + bCollider.offset.x * bTransform.scale.x,
				bTransform.position.y + bCollider.offset.y * bTransform.scale.y,
				static_cast<f32>(bCollider.width) * bTransform.scale.x,
				static_cast<f32>(bCollider.height) * bTransform.scale.y
			)) {
				Log::debug("Collision_System::update - {} collided with {}", a.id, b.id);

				// TODO(rgg): Emit an event.
			}
		}
	}
}

#ifdef PS_DEBUG

void Collision_System::debugRender(graphics::Renderer2D& renderer) {
	if (m_showBoundingBoxes) {
		for (const auto& entity : m_entities) {
			const auto& transform = entity.getComponent<Transform>();
			const auto& collider = entity.getComponent<Box_Collider>();

			SDL_Rect srcRect = {
				static_cast<int>(transform.position.x + collider.offset.x * transform.scale.x),
				static_cast<int>(transform.position.y + collider.offset.y * transform.scale.y),
				static_cast<int>(static_cast<f32>(collider.width) * transform.scale.x),
				static_cast<int>(static_cast<f32>(collider.height) * transform.scale.y)
			};

			SDL_Renderer* sdlRenderer = static_cast<SDL_Renderer*>(renderer.getContext());
			SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(sdlRenderer, &srcRect);
		}
	}
}


void Collision_System::showBoundingBoxes(bool value) {
	m_showBoundingBoxes = true;
}

#endif
