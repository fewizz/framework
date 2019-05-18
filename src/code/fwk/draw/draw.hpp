#pragma once

#include <vector>
#include <cmath>
#include <iterator>
#include <memory>
#include <functional>
#include <array>
#include "glm/mat4x4.hpp"
#include "gl/program.hpp"
#include "gl/vertex_array.hpp"
#include "gl/texture.hpp"
#include "gl/core.hpp"
#include <type_traits>
#include "../properties/with_program.hpp"

namespace gfx {

	template<class... Ext>
	struct renderer: public Ext... {};
}