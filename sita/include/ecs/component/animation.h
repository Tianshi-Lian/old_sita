#pragma once

#include <sdl2/SDL.h>

#include "core/types.h"

namespace sita::ecs::component {

	struct Animation {
		u32 frameCount;
		u32 frameSpeed;
		u32 currentFrame;
		bool shouldLoop;
		u32 startTime;

		Animation(u32 frameCount = 1, u32 frameSpeed = 1, bool shouldLoop = true)
			: frameCount(frameCount)
			, frameSpeed(frameSpeed)
			, currentFrame(1)
			, shouldLoop(shouldLoop) {
			startTime = SDL_GetTicks();
		}

	};

}
