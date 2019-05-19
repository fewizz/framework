#pragma once

#include "texture_atlas.hpp"
#include "freetype/face.hpp"
#include "index_provider.hpp"
#include "glm/vec2.hpp"
#include "glm/common.hpp"
#include "math.hpp"
#include "color.hpp"
#include <map>
#include <cmath>

namespace gfx {

inline glm::uvec2 get_max_bbox_size(freetype::face& face) {
    using namespace glm;

    auto size_metrics = face.get_size().metrics();

    uvec2 bbox_size_fu_pixels_per_em {
        face.get_bbox().size<uvec2>()
        *
        size_metrics.ppem<uvec2>()
    };

    return estd::div_ceil(
        bbox_size_fu_pixels_per_em,
        uvec2{face.units_per_em()}
    );
}

struct slot_info {
    estd::index id;
    gfx::slot slot;
    freetype::glyph_metrics* metrics;
};

namespace internal {
    std::unique_ptr<color4ub[]>
    convert_to_gl_pixel_format(freetype::bitmap&);
}


template<class Face, class TextureAtlas>
class glyph_cache {
    Face face_;
    TextureAtlas atlas;
    std::map<freetype::glyph_index, slot_info> index_to_info;

public:
    glyph_cache(Face&& face, TextureAtlas&& atlas)
    : 
    face_{std::forward<Face>(face)},
    atlas{std::forward<TextureAtlas>(atlas)} {}

    TextureAtlas& texture_atlas() {
        return atlas;
    }

    slot_info info(freetype::glyph_index index) {
        if(!index_to_info[index].id.valid()) {
            face_.load_and_render_glyph(index, freetype::render_mode::normal);
            freetype::glyph_slot& glyph = face_.glyph();
            auto data = internal::convert_to_gl_pixel_format(glyph.get_bitmap());
            auto [id, slot] = atlas.add(
                glyph.get_bitmap().size<glm::uvec2>(),
                gl::pixel_format::rgba,
                (uint8_t*)data.get()
            );
            index_to_info.insert({index, {id, slot, &glyph.get_metrics()}});
        }

        return index_to_info[index];
    }

    Face& face() { return face_; }
};

}