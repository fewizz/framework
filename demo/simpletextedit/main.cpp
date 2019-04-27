#include "glfw/window.hpp"
#include "glfw/glfw.hpp"
#include "freetype/library.hpp"
#include "gl/core.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>

using namespace std;
using namespace glfw;
using namespace freetype;
using namespace gl;

int main() {
	window w = {800, 600, "simpletextedit"};
	w.make_context_current();

	freetype::library lib;
	face* f = lib.face_from_istream(
		make_unique<ifstream>(ifstream("OldSchool.ttf", ios_base::binary))
	);
	cout << "sytle: " << f->style_name() << "\n";
	
	clear_color(1, 0, 0, 1);
	while(!w.should_close()) {
		clear(clear_buffer::color);
		w.swap_buffers();
		poll_events();
	}

	return 0;
}
