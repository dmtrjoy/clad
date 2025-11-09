#ifndef CLAD_APP_HPP
#define CLAD_APP_HPP

#include <cassert>
#include <concepts>
#include <map>
#include <memory>
#include <typeindex>
#include <utility>

#include "clad/ecs/system.hpp"

#include "event_loop.hpp"
#include "plugin.hpp"
#include "schedule.hpp"

namespace clad {

using Runner = void (*)(App&);

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
                const auto type_id { std::type_index(typeid(T)) };
                // TODO: If possible, turn this into a compile-time constraint.
                assert(m_plugins.find(type_id) == m_plugins.end());
                m_plugin_buffer.emplace_back(
                    std::make_unique<PluginHolder<T>>(std::forward<T>(plugin)));
                m_plugins.emplace(type_id,
                    std::make_unique<PluginHolder<T>>(std::forward<T>(plugin)));
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
    App& add_systems(Systems... systems)
    {
        m_schedules[std::type_index(typeid(T))].add_systems(systems...);
        return *this;
    }

    /// Builds every plugin added to this app.
    App& build() noexcept
    {
        for (auto& plugin : m_plugin_buffer) {
            plugin->build(*this);
        }
        return *this;
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
        auto* holder = static_cast<PluginHolder<T>*>(m_plugins[type_id].get());
        return holder->data;
    }

    Runner& runner() noexcept { return m_runner; }

    void startup() noexcept
    {
        assert(m_state == State::NotStarted);
        schedule<Startup>().run(m_world);
    }

    void shutdown() noexcept { schedule<Shutdown>().run(m_world); }

    [[nodiscard]] bool quit() const noexcept { return m_quit; }

    void request_quit() noexcept { m_quit = true; }

    /// Runs this app.
    void run()
    {
        assert(m_runner != nullptr);
        m_runner(*this);
    }

    template <ScheduleLabel T>
    Schedule& schedule() noexcept
    {
        const auto type_id { std::type_index(typeid(T)) };
        assert(m_schedules.find(type_id) != m_schedules.end());
        return m_schedules[type_id];
    }

    void tick()
    {
        schedule<PreUpdate>().run(m_world);
        schedule<Update>().run(m_world);
        schedule<PostUpdate>().run(m_world);
    }

    World& world() noexcept { return m_world; }

private:
    enum class State : u8 {
        NotStarted,
        Starting,
        Running,
        ShuttingDown,
        Stopped
    };

    struct PluginPlaceholder {
        PluginPlaceholder() noexcept = default;
        PluginPlaceholder(const PluginPlaceholder& other) = delete;
        PluginPlaceholder(PluginPlaceholder&& other) noexcept = delete;
        PluginPlaceholder& operator=(const PluginPlaceholder& other) = delete;
        PluginPlaceholder& operator=(PluginPlaceholder&& other) noexcept
            = delete;
        virtual ~PluginPlaceholder() = default;
        virtual void build(App& app) = 0;
    };

    template <typename T>
    struct PluginHolder final : PluginPlaceholder {
        template <typename... Args>
        explicit PluginHolder(Args&&... args)
            : data(std::forward<Args>(args)...)
        {
        }

        void build(App& app) override { data.build(app); }

        T data;
    };

    std::vector<std::unique_ptr<PluginPlaceholder>> m_plugin_buffer;
    std::map<std::type_index, std::unique_ptr<PluginPlaceholder>> m_plugins;
    std::unordered_map<std::type_index, Schedule> m_schedules = {
        { std::type_index(typeid(Startup)), Schedule {} },
        { std::type_index(typeid(PreUpdate)), Schedule {} },
        { std::type_index(typeid(Update)), Schedule {} },
        { std::type_index(typeid(PostUpdate)), Schedule {} },
        { std::type_index(typeid(Shutdown)), Schedule {} },
    };
    bool m_quit { false };
    Runner m_runner { nullptr };
    State m_state { State::NotStarted };
    World m_world;
};

} // namespace clad

#endif // !CLAD_APP_HPP
