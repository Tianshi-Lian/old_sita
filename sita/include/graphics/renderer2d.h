#pragma once

namespace sita::graphics {

	class Renderer2D {
	public:
		Renderer2D() = default;
		Renderer2D(void* context);

		[[nodiscard]] void* getContext() const;

	private:
		void* m_context;
	};

}
