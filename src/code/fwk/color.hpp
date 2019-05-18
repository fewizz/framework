#pragma once

#include <cinttypes>
#include "glm/vec4.hpp"

template<unsigned Dim, class T>
struct color : glm::vec<Dim, T> {};

template<class T>
using color1 = color<1, T>;

template<class T>
using color2 = color<2, T>;

template<class T>
using color3 = color<3, T>;

template<class T>
using color4 = color<4, T>;

using color1ub = color1<uint8_t>;
using color2ub = color2<uint8_t>;
using color3ub = color3<uint8_t>;
using color4ub = color4<uint8_t>;