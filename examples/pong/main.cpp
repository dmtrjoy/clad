#include <print>

#include "app.hpp"
#include "input.hpp"
#include "world.hpp"

namespace {

struct vec2 {
    int x;
    int y;
};

void startup(clad::world& world) { std::println("startup"); }

void update(clad::world& world)
{
    auto& input = world.resource<clad::input>();
    if (input.is_key_pressed(clad::key::up)) {
        std::println("up key is pressed");
    }
    if (input.is_key_pressed(clad::key::down)) {
        std::println("down key is pressed");
    }
    if (input.is_key_pressed(clad::key::left)) {
        std::println("left key is pressed");
    }
    if (input.is_key_pressed(clad::key::right)) {
        std::println("right key is pressed");
    }
}

void shutdown(clad::world& world) { std::println("shutdown"); }

} // namespace

int main()
{
    clad::app app;
    app.add_system(clad::event::startup, startup)
        .add_system(clad::event::update, update)
        .add_system(clad::event::shutdown, shutdown)
        .run();
}
