#pragma once

#include <utility>

#include "core/types.h"

namespace sita::ecs::component {

	struct Sprite {
		std::string assetId;
		u32 width;
		u32 height;
		i32 layer;
		u32 srcX;
		u32 srcY;

		Sprite(std::string assetId = "", u32 width = 0, u32 height = 0, i32 layer = 0, u32 srcX = 0, u32 srcY = 0)
			: assetId(std::move(assetId))
			, width(width)
			, height(height)
			, layer(layer)
			, srcX(srcX)
			, srcY(srcY) {
		}
	};

}
