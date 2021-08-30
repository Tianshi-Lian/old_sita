#pragma once

#include <vector>

#include "ecs/entity/entity.h"
#include "ecs/component/component.h"

#include "graphics/renderer2d.h"

namespace sita::ecs::system {

	enum class System_Flags : u32 {
		None = 0,
		Updateable = 1,
		Renderable = 2
	};

	inline System_Flags operator |(System_Flags a, System_Flags b) {
		return static_cast<System_Flags>(static_cast<u32>(a) | static_cast<u32>(b));
	}

	inline bool operator &(System_Flags a, System_Flags b) {
		return static_cast<u32>(a) & static_cast<u32>(b);
	}

	class System {
	public:
		System(System_Flags systemFlags = System_Flags::None);
		virtual ~System() = default;

		void addEntity(entity::Entity entity);
		void removeEntity(entity::Entity entity);

		virtual void update(const float& dt);
		virtual void render(graphics::Renderer2D& renderer);

#ifdef PS_DEBUG
		virtual void debugRender(graphics::Renderer2D& renderer);
#endif

		[[nodiscard]] const std::vector<entity::Entity>& getEntities() const;
		[[nodiscard]] const component::Base_Component::Signature& getSignature() const;
		[[nodiscard]] System_Flags getFlags() const;

		template <typename T> void requireComponent();

	protected:
		virtual void postAddEntity(entity::Entity& entity);

		std::vector<entity::Entity> m_entities;

	private:
		component::Base_Component::Signature m_signature;
		System_Flags m_flags;
	};

	template <typename T>
	void System::requireComponent() {
		const auto componentId = component::Component<T>::getId();
		m_signature.set(componentId);
	}

}
