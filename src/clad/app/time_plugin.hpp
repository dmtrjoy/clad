#ifndef CLAD_TIME_PLUGIN_HPP
#define CLAD_TIME_PLUGIN_HPP

#include <chrono>

#include "app.hpp"
#include "clad/ecs/world.hpp"

namespace clad {

struct TimePlugin {

    static void build(App& app)
    {
        // do stuff
        // an more
    }

    static void update(World& world)
    {
        const auto now { std::chrono::steady_clock::now() };
    }

    float delta;
};

} // namespace clad

#endif // !CLAD_TIME_PLUGIN_HPP
