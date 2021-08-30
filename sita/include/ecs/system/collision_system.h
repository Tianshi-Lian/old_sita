#pragma once

#include "system.h"

namespace sita::ecs::system {

	class Collision_System : public System {
	public:
		Collision_System();

		void update(const float& dt) override;

#ifdef PS_DEBUG

		void debugRender(graphics::Renderer2D& renderer) override;

		void showBoundingBoxes(bool value);

	private:
		bool m_showBoundingBoxes;

#endif

	};

}
