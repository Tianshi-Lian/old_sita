#include "ecs/system/render_system.h"

#include <algorithm>
#include <SDL2/SDL.h>

#include "assets/asset_manager.h"
#include "ecs/ecs.h"

using namespace sita::ecs::system;
using namespace sita::ecs::component;

Render_System::Render_System(std::shared_ptr<assets::Asset_Manager> assetManager)
	: System(System_Flags::Renderable)
	, m_assetManager(std::move(assetManager)) {
	requireComponent<Transform>();
	requireComponent<Sprite>();
}

void Render_System::render(graphics::Renderer2D& renderer) {
	for (auto entity : m_entities) {
		const auto& transform = entity.getComponent<Transform>();
		const auto& sprite = entity.getComponent<Sprite>();

		SDL_Rect srcRect = {
			static_cast<int>(sprite.srcX),
			static_cast<int>(sprite.srcY),
			static_cast<int>(sprite.width),
			static_cast<int>(sprite.height)
		};

		SDL_Rect dstRect = {
			static_cast<int>(transform.position.x),
			static_cast<int>(transform.position.y),
			static_cast<int>(sprite.width * transform.scale.x),
			static_cast<int>(sprite.height * transform.scale.y)
		};

		const auto sdlRenderer = static_cast<SDL_Renderer*>(renderer.getContext());
		const auto texture = m_assetManager->getTexture(sprite.assetId);
		SDL_RenderCopyEx(sdlRenderer, texture, &srcRect, &dstRect, transform.rotation, nullptr, SDL_FLIP_NONE);
	}
}

void Render_System::postAddEntity(entity::Entity&) {
	std::sort(m_entities.begin(), m_entities.end(),
		[](const entity::Entity& a, const entity::Entity& b) {
			const auto& sprA = a.getComponent<Sprite>();
			const auto& sprB = b.getComponent<Sprite>();

			return sprA.layer < sprB.layer;
		}
	);
}
