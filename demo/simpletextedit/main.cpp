#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>

#include "glfw/window.hpp"
#include "glfw/glfw.hpp"
#include "freetype/library.hpp"
#include "gl/core.hpp"
#include "fwk/draw/text_drawer.hpp"
#include "fwk/shaders.hpp"

using namespace std;
using namespace glfw;
using namespace gl;
using namespace fwk;

int main() {
	window w = {800, 600, "simpletextedit"};
	w.make_context_current();

	freetype::library lib;
	auto face = lib.face_from_istream(
		ifstream("OldSchool.ttf", ios_base::binary)
	);
	face.set_char_size(64*72, 64*72, 100, 100);

	gfx::glyph_cache cache{
		std::move(face),
		gfx::texture_atlas(
			{1000, 1000},
			gfx::fixed_slot_container(
				{100, 100},
				{10, 10}
			)
		)
	};

	auto resources_path = filesystem::path{"./"}
		.parent_path().parent_path()
		/"src/resources/";

	program text_program {
		load<vertex_shader>(
			resources_path/"shaders/passtrough_u_mat4_a_pos2_a_uv.vs"
		),
		load<fragment_shader>(
			resources_path/"shaders/passtrough_u_tex2_a_uv.fs"
		)
	};

	gfx::text_drawer drawer {
		std::string{"Hello world!"},
		std::move(cache),
		std::move(text_program),
		gfx::text_drawer_origin::baseline_start
	};

	clear_color(1, 0, 0, 1);

	while(!w.should_close()) {
		clear(clear_buffer::color);
		w.swap_buffers();
		poll_events();
	}

	return 0;
}
