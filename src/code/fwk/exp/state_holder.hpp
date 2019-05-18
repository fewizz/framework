#pragma once

#include <memory>
#include <type_traits>

namespace estd {

template <class T, class Base = T>
class state_holder {
    static_assert(
        std::is_base_of_v<Base, std::remove_reference_t<T>>
    );

    T t;
public:
    state_holder(T&& t): t{std::forward<T>(t)} {}

    std::add_pointer_t<
        std::remove_reference_t<T>
    > 
    operator->() {
        return &t;
    }
};

}