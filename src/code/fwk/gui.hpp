#pragma once

#include <memory>
#include "properties/drawable.hpp"
#include "properties/updatable.hpp"
#include "properties/with_size.hpp"
#include "glm/vec2.hpp"
#include "glfw/window.hpp"

namespace osu {
	extern std::unique_ptr<glfw::window> window;
}

namespace gui {

	template<class... Props>
	class view : public Props... {
	};

	template<class... Props>
	struct screen :
	public view<
		prop::updatable,
		prop::drawable<>,
		prop::with_size<glm::uvec2, unsigned>,
		Props...
	> {
		glm::uvec2 get_size() override {
			return osu::window->framebuffer_size<glm::uvec2>();
		}

	};

}