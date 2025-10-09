#ifndef CLAD_SCHEDULE_HPP
#define CLAD_SCHEDULE_HPP

#include <vector>

#include "system.hpp"
#include "world.hpp"

namespace clad {

class schedule {
public:
    schedule& add_system(system system);

    void run(world& world) const;

private:
    std::vector<system> m_systems;
};

} // namespace clad

#endif // !CLAD_SCHEDULE_HPP
