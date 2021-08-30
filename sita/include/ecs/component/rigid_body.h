#pragma once

#include "core/types.h"

namespace sita::ecs::component {

	struct Rigid_Body {
		v2 velocity;

		Rigid_Body(v2 velocity = { 0.0f, 0.0f })
			: velocity(velocity) {
		}
	};

}
