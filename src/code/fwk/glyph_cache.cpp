#include "glyph_cache.hpp"
#include "gl/texture.hpp"

using namespace std;
using namespace freetype;
using namespace gfx;
using namespace glm;

unique_ptr<uint8_t[]>
gfx::internal::convert_to_gl_pixel_format(gl::pixel_format pf, glyph_slot& gs) {
    freetype::bitmap bitmap = gs.get_bitmap();
    uint w = bitmap.width();
    uint h = bitmap.rows();
    uint pitch = bitmap.pitch();
    auto data = make_unique<uint8_t[]>(w * h * 4);
    auto data0 = bitmap.data<uint8_t>();

    pixel_mode bm_pm = bitmap.pixel_mode;

    for (uint y = 0; y < h; y++) {
        uint row_beginning = y * pitch;

        for (uint x = 0; x < w; x++) {
            uint8_t c = data0[x + row_beginning];

            uint pixel = x + y * w;
            data[pixel * 4] = 0xFF;
            data[pixel * 4 + 1] = 0xFF;
            data[pixel * 4 + 2] = 0xFF;
            data[pixel * 4 + 3] = c;
        }
    }

    return data;
}