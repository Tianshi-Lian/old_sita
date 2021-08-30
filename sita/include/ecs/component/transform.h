#pragma once

#include "core/types.h"

namespace sita::ecs::component {

	struct Transform {
		v2 position;
		v2 scale;
		f64 rotation;

		Transform(v2 position = { 0.0f, 0.0f }, v2 scale = { 1.0f, 1.0f }, f64 rotation = 0.0)
			: position(position)
			, scale(scale)
			, rotation(rotation) {
		}
	};

}
