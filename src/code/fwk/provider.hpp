#pragma once

namespace estd {

template<class R, class... Args>
struct provider {

virtual R provide(Args...) = 0;

};

}