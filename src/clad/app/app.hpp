#ifndef CLAD_APP_HPP
#define CLAD_APP_HPP

#include <cassert>
#include <concepts>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "clad/app/event_loop.hpp"
#include "clad/ecs/system.hpp"
#include "clad/std/any.hpp"

#include "plugin.hpp"
#include "schedule.hpp"

namespace clad {

struct Startup { };
struct PreUpdate { };
struct Update { };
struct PostUpdate { };
struct Shutdown { };

class App {
public:
    App() { m_world.emplace<EventLoop>(); }

    /// Adds one or more `::Plugin`s to this app.
    ///
    /// \tparam Plugins The types of plugins to add.
    /// \param plugins The plugins to add.
    /// \return A reference to this app.
    template <typename... Plugins>
        requires((TransferablePlugin<Plugins> && ...))
    App& add_plugins(Plugins&&... plugins) noexcept
    {
        (
            [&]<typename T>(T&& plugin) {
                // TODO: If possible, turn this into a compile-time constraint.
                const auto type_id { std::type_index(typeid(T)) };
                assert(m_plugins.find(type_id) == m_plugins.end());
                m_plugins.emplace(type_id, std::forward<T>(plugin));
            }(std::forward<Plugins>(plugins)),
            ...);
        return *this;
    }

    /// Adds one or more `::System`s to a `::Schedule`.
    ///
    /// \tparam T The schedule label.
    /// \tparam Systems The types of systems to add.
    /// \param systems The systems to add.
    /// \return A reference to this app.
    template <ScheduleLabel T, typename... Systems>
        requires((std::same_as<Systems, System>) && ...)
    App& add_systems(const Systems... systems)
    {
        m_schedules[std::type_index(typeid(T))].add_systems(systems...);
        return *this;
    }

    void build() noexcept
    {
        for (auto& it : m_plugins) {
            // TODO: Call build() on each plugin. Will need type erasure.
        }
    }

    template <typename T, typename... Args>
    void emplace_resource(Args&&... args) noexcept
    {
        m_world.emplace<T>(std::forward<Args>(args)...);
    }

    template <Plugin T>
    T& plugin() noexcept
    {
        const auto type_id { std::type_index(typeid(T)) };
        assert(m_plugins.find(type_id) != m_plugins.end());
        return any_cast<T>(m_plugins[type_id]);
    }

    /// Runs this app.
    void run();

    template <ScheduleLabel T>
    Schedule& schedule() noexcept
    {
        const auto type_id { std::type_index(typeid(T)) };
        assert(m_schedules.find(type_id) != m_schedules.end());
        return m_schedules[type_id];
    }

    World& world() noexcept { return m_world; }

private:
    World m_world;
    std::unordered_map<std::type_index, any> m_plugins;
    std::unordered_map<std::type_index, Schedule> m_schedules;
    bool m_running { true };
};

} // namespace clad

#endif // !CLAD_APP_HPP
