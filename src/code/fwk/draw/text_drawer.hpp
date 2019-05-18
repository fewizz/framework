#pragma once

#include "freetype/face.hpp"
#include "draw.hpp"
#include <memory>
#include <string>
#include "utf8.h"
#include "../texture_atlas.hpp"
#include <algorithm>
#include <cmath>
#include <map>
#include "gl/core.hpp"
#include "../glyph_cache.hpp"

namespace gfx {

	enum class text_drawer_origin {
		top_left,
		baseline_start
	};

	template<
		class GlyphCache,
		class Program
	>
	class text_drawer
	{
		GlyphCache cache;
		std::string text;
		std::vector<int> textures_array_texture_units;
		gl::array_buffer positions;
		gl::array_buffer uvs;
		float width;
		size_t chars;
	public:

		text_drawer(
			std::string str,
			GlyphCache&& cache,
			Program&& program,
			text_drawer_origin o
		);

		void draw();

		float pixels_width() {
			return width;
		}

		decltype(cache.texture_atlas()) texture_atlas() {
			return cache.texture_atlas();
		}

		GlyphCache glyph_cache() {
			return cache;
		}
	};

}