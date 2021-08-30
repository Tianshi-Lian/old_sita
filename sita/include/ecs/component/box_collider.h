#pragma once

#include "core/types.h"

namespace sita::ecs::component {

	struct Box_Collider {
		u32 width;
		u32 height;
		v2 offset;
		
		Box_Collider(u32 width = 0, u32 height = 0, v2 offset = { 0.0f, 0.0f })
			: width(width)
			, height(height)
			, offset(offset) {
		}
	};

}
