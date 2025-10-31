#ifndef CLAD_SCHEDULE_HPP
#define CLAD_SCHEDULE_HPP

#include <vector>

#include "clad/ecs/system.hpp"
#include "clad/ecs/world.hpp"

namespace clad {

class Schedule {
public:
    /// Adds one or more `::System`s to to this schedule.
    ///
    /// \tparam Args The types of arguments to forward. Restricted to the
    ///     `::System` type.
    /// \param systems The systems to add.
    /// \return A reference to this schedule.
    template <typename... Args>
        requires((std::same_as<Args, System>) && ...)
    Schedule& add(const Args... systems) noexcept
    {
        (m_systems.push_back(std::move(systems)), ...);
        return *this;
    }

    /// Runs the systems in this schedule.
    ///
    /// \param A reference to a `::World`.
    void run(World& world) const;

private:
    std::vector<System> m_systems;
};

} // namespace clad

#endif // !CLAD_SCHEDULE_HPP
