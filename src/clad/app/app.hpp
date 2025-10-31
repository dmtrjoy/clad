#ifndef CLAD_APP_HPP
#define CLAD_APP_HPP

#include <array>
#include <concepts>
#include <utility>

#include "clad/app/event_loop.hpp"
#include "clad/ecs/system.hpp"

#include "event.hpp"
#include "feature.hpp"
#include "schedule.hpp"

namespace clad {

class App {
public:
    App() { m_world.emplace<EventLoop>(); }

    template <typename Resource, typename... Args>
    void emplace(Args&&... args)
    {
        m_world.emplace<Resource>(std::forward<Args>(args)...);
    }

    /// Installs one or more `::Feature`s into this app.
    template <Feature... Features>
    App& install()
    {
        (install(Features {}), ...);
        return *this;
    }

    /// Schedules one or more `::System`s to run during an `::Event`.
    ///
    /// \tparam Systems The types of systems to schedule.
    /// \param event The event to run during.
    /// \param systems The systems to schedule.
    /// \return A reference to this app.
    template <typename... Systems>
        requires((std::same_as<Systems, System>) && ...)
    App& schedule(const Event event, const Systems... systems)
    {
        const auto event_idx { std::to_underlying(event) };
        m_schedules[event_idx].add(systems...);
        return *this;
    }

    void send(const Event event)
    {
        if (event == Event::Shutdown) {
            m_running = true;
        }
    }

    /// Runs this app.
    void run();

    World& world() noexcept { return m_world; }

private:
    template <Feature Feature>
    void install(Feature&& feature)
    {
        feature.build(*this);
    }

    World m_world;
    std::array<Schedule, static_cast<size_t>(Event::Count)> m_schedules {};
    bool m_running { true };
};

} // namespace clad

#endif // !CLAD_APP_HPP
