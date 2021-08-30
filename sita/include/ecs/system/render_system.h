#pragma once

#include <memory>
#include <unordered_map>

#include "system.h"

namespace sita::assets {
	class Asset_Manager;
}

namespace sita::ecs::system {

	class Render_System : public System {
	public:
		Render_System(std::shared_ptr<assets::Asset_Manager> assetManager);

		void render(graphics::Renderer2D& renderer) override;

	protected:
		void postAddEntity(entity::Entity& entity) override;

	private:
		std::shared_ptr<assets::Asset_Manager> m_assetManager;

		std::unordered_map<u32, entity::Entity*> m_entityLayers;
	};

}
