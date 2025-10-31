#ifndef CLAD_EVENT_HPP
#define CLAD_EVENT_HPP

#include "clad/std/types.hpp"

namespace clad {

enum class Event : u8 {
    Startup,
    PreUpdate,
    Update,
    PostUpdate,
    Shutdown,
    Count, // Represents the number of `::Event` enums.
};

} // namespace clad

#endif // !CLAD_EVENT_HPP
