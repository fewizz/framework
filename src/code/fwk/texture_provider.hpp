#pragma once

#include "provider.hpp"
#include "gl/texture.hpp"
#include "glm/vec2.hpp"

namespace gfx {

template<class Tex>
using texture_provider = estd::provider<Tex()>;

class fixed_size_texture_provider : public texture_provider<gl::texture_2d>{

    glm::ivec2 dim;
    gl::internal_format inf;
    gl::pixel_format pf;

    fixed_size_texture_provider(
        glm::ivec2 dim, 
        gl::internal_format inf,
        gl::pixel_format pf
    )
    :
    dim{dim},
    inf{inf},
    pf{pf} {}

    gl::texture_2d provide() override {
        gl::texture_2d tex;
        tex.image(
            inf,
            dim[0],
            dim[1],
            pf, 
            (void*)nullptr
        );
        return tex;
    }

};


}