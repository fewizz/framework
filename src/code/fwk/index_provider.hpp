#pragma once

#include <memory>
#include <list>
#include "provider.hpp"
#include "math.hpp"

namespace estd {

class index {
    intmax_t val;
public:
    index():val{-1}{}
    index(intmax_t v):val{v}{}
    index& operator=(const index&) = default;

    operator intmax_t() const {
        return val;
    }

    bool valid() const { return val != -1; }
};

class index_provider : public estd::provider<index> {
    virtual void free(index s) = 0;
};

class static_index_provider : public index_provider {
    static constexpr uint bits = sizeof(uintmax_t)*8;
    uint size;
    std::unique_ptr<uintmax_t[]> v;
public:
    static_index_provider(uint indexes)
    :
    size {estd::div_ceil(indexes, bits)},
    v{std::make_unique<uintmax_t[]>(size)}
    {}

    index provide() override {
        for(uint i = 0; i < size; i++) {
            uintmax_t& v0 = v[i];

            if(~v0 == 0)
                continue;

            uint_fast16_t x = 0;
            while(((v0 >> x) & 0x1) != 0)
                x++;

            v0 |= 1 << x;

            return i * bits + x;
        }

        throw std::runtime_error("free index not found");
    }

    void free(index s) override {
        v[s / bits] &= 0 << (s % bits);
    }
};

}