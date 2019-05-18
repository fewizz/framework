#include "texture_atlas.hpp"

using namespace gfx;
using namespace std;
using namespace glm;

pair<index, slot>
gfx::fixed_slot_container::occupy(uvec2 tex_dim)
{
    index id = ip.provide();

    uvec2 coord {
        (id % slots[0]) * slot_dim[0],
        (id / slots[0]) * slot_dim[1]
    };

    slot s{coord, tex_dim};
    pair result(id, s);
    map.insert(result);
    return result;
}