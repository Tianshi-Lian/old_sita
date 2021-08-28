#pragma once

#include <bitset>

#include "core/types.h"

namespace sita::ecs::component {

	constexpr u32 MAX_COMPONENTS = 32;

	struct Base_Component {
		typedef std::bitset<MAX_COMPONENTS> Signature;
		
	protected:
		static int m_nextId;
	};

	template <typename T>
	struct Component : Base_Component {
		static int getId();
	};

	template <typename T>
	int Component<T>::getId() {
		static auto id = m_nextId++;
		return id;
	}

}
