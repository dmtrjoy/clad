#include "app.hpp"

#include "event_loop.hpp"

namespace clad {

void App::run()
{
    m_schedules[std::to_underlying(Event::Startup)].run(m_world);
    while (m_running) {
        auto& event_loop { m_world.resource<EventLoop>() };
        while (!event_loop.empty()) {
            const Event event { event_loop.next() };
            if (event == Event::Shutdown) {
                m_running = false;
            }
        }
        m_schedules[std::to_underlying(Event::PreUpdate)].run(m_world);
        m_schedules[std::to_underlying(Event::Update)].run(m_world);
        m_schedules[std::to_underlying(Event::PostUpdate)].run(m_world);
    }
    m_schedules[std::to_underlying(Event::Shutdown)].run(m_world);
}

} // namespace clad
