#include "graphics/renderer2d.h"

using namespace sita::graphics;

Renderer2D::Renderer2D(void* context)
	: m_context(context) {
}

void* Renderer2D::getContext() const {
	return m_context;
}
