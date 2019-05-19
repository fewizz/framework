#include "glyph_cache.hpp"
#include "gl/texture.hpp"
#include "color.hpp"
#include "math.h"

using namespace std;
using namespace gfx;
using namespace glm;

namespace {

    template<class Fun>
    unique_ptr<color4ub[]> convert(
        freetype::bitmap& bitmap,
        Fun fun
    ) {
        uvec2 size = bitmap.size<uvec2>();
        uint pitch = bitmap.pitch();
        auto data = make_unique<color4ub[]>(size[0] * size[1] * 4);
        auto data0 = bitmap.data<uint8_t>();

        for (uint y = 0; y < size[1]; y++) {
            uint row_beginning = y * pitch;

            for (uint x = 0; x < size[0]; x++) {
                data[y*size[0] + x] = fun(x, data0 + row_beginning);
            }
        }

        return data;
    }

    unique_ptr<color4ub[]> gray(freetype::bitmap& bm) {
        return convert(bm, [&](uint x, uint8_t* data) {
            uint8_t color = data[x];
            uint8_t final_color = estd::div_ceil(color*255, bm.num_grays());
            return color4ub{ final_color };
        });
    }
}

unique_ptr<color4ub[]>
gfx::internal::convert_to_gl_pixel_format(freetype::bitmap& bitmap) {
    if(bitmap.pixel_mode() == freetype::gray) {
        return gray(bitmap);
    }
    else throw runtime_error("unsupported pixel mode");

    
}