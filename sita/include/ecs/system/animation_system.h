#pragma once

#include "system.h"

namespace sita::ecs::system {

	class Animation_System : public System {
	public:
		Animation_System();

		void update(const float& dt) override;
	};

}
