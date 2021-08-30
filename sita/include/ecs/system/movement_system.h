#pragma once

#include "system.h"

namespace sita::ecs::system {

	class Movement_System : public System {
	public:
		Movement_System();

		void update(const float& dt) override;
	};

}
