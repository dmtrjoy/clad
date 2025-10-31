#ifndef CLAD_SPRITE_HPP
#define CLAD_SPRITE_HPP

#include "clad/color/color.hpp"
#include "clad/math/vec.hpp"

namespace clad {

struct Sprite {
    Color color { Color::Transparent };
    Vec2 size { .x = 0.0, .y = 0.0 };
};

} // namespace clad

#endif // !CLAD_SPRITE_HPP
