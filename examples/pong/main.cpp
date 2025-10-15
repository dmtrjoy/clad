#include <print>

#include "app.hpp"
#include "color.hpp"
#include "entity.hpp"
#include "input.hpp"
#include "sprite.hpp"
#include "transform.hpp"
#include "vec2.hpp"
#include "world.hpp"

namespace {

struct ball { };

void startup(clad::world& world)
{
    std::println("startup");

    const clad::entity e { world.create() };

    world.emplace<ball>(e);
    world.emplace<clad::sprite>(
        e, clad::color::white, clad::vec2 { .x = 12.0, .y = 12.0 });
    world.emplace<clad::transform>(e, 395.0, 295.0);
}

void update(clad::world& world)
{
    world.view<ball, clad::transform>(
        [&world](
            const clad::entity entity, ball& ball, clad::transform& transform) {
            auto& input = world.resource<clad::input>();
            if (input.is_key_pressed(clad::key::up)) {
                std::println("up key is pressed");
                transform.y -= 1.0;
            }
            if (input.is_key_pressed(clad::key::down)) {
                std::println("down key is pressed");
                transform.y += 1.0;
            }
            if (input.is_key_pressed(clad::key::left)) {
                std::println("left key is pressed");
                transform.x -= 1.0;
            }
            if (input.is_key_pressed(clad::key::right)) {
                std::println("right key is pressed");
                transform.x += 1.0;
            }
        });
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
