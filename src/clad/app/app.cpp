#include "app.hpp"

#include "event_loop.hpp"

namespace clad {

void App::run()
{
    schedule<Startup>().run(m_world);
    while (m_running) {
        auto& event_loop { m_world.resource<EventLoop>() };
        while (!event_loop.empty()) {
            const Event event { event_loop.next() };
            if (event == Event::Shutdown) {
                m_running = false;
            }
        }
        schedule<PreUpdate>().run(m_world);
        schedule<Update>().run(m_world);
        schedule<PostUpdate>().run(m_world);
    }
    schedule<Shutdown>().run(m_world);
}

} // namespace clad
