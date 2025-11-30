#ifndef CLAD_COMPONENT_HPP
#define CLAD_COMPONENT_HPP

#include "tick.hpp"

namespace clad {

struct ComponentMetadata {
    Tick added_tick;
    Tick changed_tick;
};

} // namespace clad

#endif // !CLAD_COMPONENT_HPP
