#ifndef CLAD_WINDOW_PLUGIN_HPP
#define CLAD_WINDOW_PLUGIN_HPP

#include "clad/ecs/entity.hpp"
#include "clad/ecs/world.hpp"
#include "clad/window/window.hpp"

#include "app.hpp"

namespace clad {

struct WindowPlugin {
    static void build(App& app) { }

    static void startup(World& world) noexcept
    {
        const Entity window { world.create() };
        world.emplace<Window>(window, "title", 800, 600);
    }
};

} // namespace clad

#endif // !CLAD_WINDOW_PLUGIN_HPP
