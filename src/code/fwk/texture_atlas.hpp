#pragma once

#include "gl/texture.hpp"
#include <vector>
#include <list>
#include <cmath>
#include <utility>
#include "glm/vec2.hpp"
#include <map>
#include <numeric>
#include "index_provider.hpp"

namespace gfx {

	struct slot {
		const glm::uvec2 position;
		const glm::uvec2 dimension;
	public:
		slot():position{0}, dimension{0} {}
		slot(glm::uvec2 p, glm::uvec2 d)
		:position{p}, dimension{d} {}
		slot(const slot&) = default;
		slot(slot&&) = default;
	};

	class slot_container {
	public:
		virtual std::pair<estd::index, slot> occupy(glm::uvec2 tex_dim) = 0;

		virtual slot get_slot(estd::index id) = 0;

		virtual void free(estd::index) = 0;
		virtual ~slot_container() = default;
	};

	template<class SlotContainer>
	class texture_atlas : public gl::texture_2d {
		SlotContainer sc;
 	public:

		texture_atlas(glm::uvec2 dimension, SlotContainer&& sc)
		: sc{std::forward(sc)}
		{
    		image(
        		gl::internal_format::rgba8,
        		dimension[0],
        		dimension[1],
        		gl::pixel_format::rgba,
        		(void*)nullptr
    		);
		}

		texture_atlas(texture_atlas&& r) = default;
		texture_atlas& operator=(texture_atlas&& r) = default;

		std::pair<estd::index, slot>
		add(glm::uvec2 dimension, gl::pixel_format pixel_format, uint8_t* data) {
    		auto [id, slot] = sc.occupy(dimension);

    		sub_image(
        		slot.position.x,
        		slot.position.y,
        		slot.dimension[0],
        		slot.dimension[1],
        		pixel_format,
        		data
    		);

    		return {id, slot};
		}

		slot get(estd::index id) {
			return sc.get_slot(id);
		}
	};

	class fixed_slot_container : public slot_container {
		glm::uvec2 slot_dim;
		glm::uvec2 slots;

		std::map<estd::index, slot> map;
		estd::static_index_provider ip;
	public:
		fixed_slot_container (
			glm::uvec2 slot,
			glm::uvec2 slots
		):
		slot_dim{slot},
		slots{slots},
		ip{slots[0]*slots[1]}
		{}

		std::pair<estd::index, slot>
		occupy(glm::uvec2 tex_dim) override;

		inline slot get_slot(estd::index id) override {
			return map[id];
		};

		inline void free(estd::index id) override {
			ip.free(id);
		}
	};
}