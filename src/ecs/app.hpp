#ifndef CLAD_APP_HPP
#define CLAD_APP_HPP

#include <array>

#include "schedule.hpp"
#include "system.hpp"
#include "types.hpp"

namespace clad {

enum class event : u8 {
    startup,
    update,
    shutdown,
    count, // Represents the number of event enums.
};

class app {
public:
    /// Adds a system to run on a given event.
    app& add_system(event event, system system);

    /// Runs the app.
    void run();

private:
    world m_world;
    std::array<schedule, static_cast<size_t>(event::count)> m_schedules = {};
};

} // namespace clad

#endif // !CLAD_APP_HPP
