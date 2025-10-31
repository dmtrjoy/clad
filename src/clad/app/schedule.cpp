#include "schedule.hpp"

#include "clad/ecs/system.hpp"
#include "clad/ecs/world.hpp"

namespace clad {

void Schedule::run(World& world) const
{
    for (const System system : m_systems) {
        system(world);
    }
}

} // namespace clad
