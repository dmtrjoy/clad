#ifndef CLAD_SPRITE_HPP
#define CLAD_SPRITE_HPP

#include "color.hpp"
#include "vec2.hpp"

namespace clad {

struct sprite {
    color color { color::transparent };
    vec2 size { .x = 0.0, .y = 0.0 };
};

} // namespace clad

#endif // !CLAD_SPRITE_HPP
