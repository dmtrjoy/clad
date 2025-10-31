#ifndef CLAD_EVENT_LOOP_HPP
#define CLAD_EVENT_LOOP_HPP

#include <cassert>
#include <queue>

#include "event.hpp"

namespace clad {

class EventLoop {
public:
    bool empty() { return m_queue.empty(); }
    Event next()
    {
        assert(!empty());
        const Event next { m_queue.front() };
        m_queue.pop();
        return next;
    }
    void send(const Event event) { m_queue.push(event); }

private:
    std::queue<Event> m_queue;
};

} // namespace clad

#endif // !CLAD_EVENT_LOOP_HPP
