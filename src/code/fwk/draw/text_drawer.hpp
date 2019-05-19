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
		)
		:
		cache{std::forward<GlyphCache>(cache)}
		{
		    freetype::face& face = cache.face();
		    std::vector<float> positions;
		    std::vector<float> uvs;

		    glm::uvec2 pen;
			glm::uvec2 off;

		    if(o == text_drawer_origin::top_left) {
		        off.y = -face.get_size().metrics().height();
		    }

			glm::vec2 scale{1.0 / 64.0};

		    auto begin = str.begin();
		    while(begin != str.end()) {
		        uint32_t code_point = utf8::next(begin, str.end());

		        if (code_point == '\n') {
		            pen.y -= (double)face.get_size().metrics().height();
		            pen.x = 0;
		            continue;
		        }

		        auto [id, slot, metrics] =
		            cache.info(face.get_char_index(code_point));

		        if (metrics->height() == 0 && metrics->width() == 0) {
		            pen.x += metrics->horizontal_advance();
		            continue;
		        }

		        //float left = (penX + metrics.horizontal_bearing_x()) * scaleX;
		        //float right = (penX + metrics.horizontal_bearing_x() + metrics.width()) * scaleX;
		        //float bot = (penY + offY + metrics.horizontal_bearing_y() - metrics.height()) * scaleY;
		        //float top = (penY + offY + metrics.horizontal_bearing_y()) * scaleY;

				glm::vec2 left_top{pen + metrics->template horizontal_bearing<glm::uvec2>()};
				glm::vec2 bot_right{left_top - metrics->template size<glm::vec2>()};

				left_top *= scale;
				bot_right *= scale;

		        positions.insert(positions.end(),
		        {
		            left_top.x, bot_right.y,
		            bot_right.x, bot_right.y,
		            bot_right.x, left_top.y,
		            left_top.x, bot_right.y,
		            bot_right.x, left_top.y,
		            left_top.x, left_top.y
		        });

		        //cout << "met: " << metrics.width() << " " << metrics.height() << "\n";
		        float x = slot.position.x / (float)cache.texture_atlas().width();
		        float y = slot.position.y / (float)cache.texture_atlas().height();
		        float w = metrics->width() / 64.0f / (float)cache.texture_atlas().width();
		        float h = metrics->height() / 64.0f / (float)cache.texture_atlas().height();

		        uvs.insert(uvs.end(),
		        {
		            x, y+h,
		            x+w, y+h,
		            x+w, y,
		            x, y+h,
		            x+w, y,
		            x, y,
		        });

		        pen.x += metrics->horizontal_advance();
		    }

		    this->positions.data(positions);
		    this->uvs.data(uvs);

		    width = pen.x * scale.x;
		}

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