#pragma once

namespace estd {

    template<class T0, class T1, class T2=T0>
    T2 div_ceil(T0 t0, T1 t1) {
        return (t0 + t1 - (t0 % t1)) / t1;
    }
}