#pragma once

#include <string>
#include "gl/shader.hpp"
#include <fstream>
#include <filesystem>
#include "unsafe_iostream_operations.hpp"

namespace fwk {

template<class Shader>
std::enable_if_t<std::is_base_of_v<gl::shader, Shader>,
Shader> load(std::filesystem::path path) {
    if(!std::filesystem::exists(path))
        throw std::runtime_error("shader \"" + path.string() + "\" not found\n");
    
    std::ifstream stream(path, std::ios::binary);
    size_t size = estd::distance_to_end(stream);
    auto data_ptr = estd::get<char*>(stream, size);
    Shader sh(data_ptr.get());
    sh.compile();
    return sh;
}

}