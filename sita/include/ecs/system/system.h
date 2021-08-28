#pragma once

#include <vector>

#include "ecs/component/component.h"

namespace sita::ecs::system {

	class System {
	public:
		System() = default;
		virtual ~System() = default;

		void addEntity(u64 entityId);
		void removeEntity(u64 entityId);

		[[nodiscard]] const std::vector<u64>& getEntities() const;
		[[nodiscard]] const component::Base_Component::Signature& getSignature() const;

		template <typename T> void requireComponent();

	private:
		component::Base_Component::Signature m_signature;
		std::vector<u64> m_entities;
	};

	template <typename T>
	void System::requireComponent() {
		const auto componentId = component::Component<T>::getId();
		m_signature.set(componentId);
	}

}
