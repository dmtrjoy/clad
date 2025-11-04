#include <print>

#include "clad/app/app.hpp"
#include "clad/app/event_loop.hpp"
#include "clad/color/color.hpp"
#include "clad/ecs/entity.hpp"
#include "clad/ecs/world.hpp"
#include "clad/input/input.hpp"
#include "clad/math/vec.hpp"
#include "clad/render/renderer.hpp"
#include "clad/sprite/sprite.hpp"
#include "clad/sprite/transform.hpp"
#include "clad/window/window.hpp"

#include "SDL3/SDL_init.h"

namespace {

struct Input {
    static void build(clad::App& app)
    {
        app.emplace_resource<clad::Input>();
        app.add_systems<clad::Update>(poll);
    }

    static void poll(clad::World& world)
    {
        auto& event_loop = world.resource<clad::EventLoop>();
        auto& input = world.resource<clad::Input>();
        input.poll();
        if (input.quit()) {
            event_loop.send(clad::Event::Shutdown);
        }
    }
};

struct Render {
    static void build(clad::App& app)
    {
        clad::World& world { app.world() };
        auto& window { world.resource<clad::Window>() };
        app.emplace_resource<clad::Renderer>(window);
        app.add_systems<clad::PreUpdate>(clear);
        app.add_systems<clad::Update>(render);
        app.add_systems<clad::PostUpdate>(present);
    }

    static void clear(clad::World& world)
    {
        auto& renderer { world.resource<clad::Renderer>() };
        renderer.clear();
    }

    static void render(clad::World& world)
    {
        world.view<clad::Sprite, clad::Transform>(
            [&world](const clad::Entity /*entity*/, clad::Sprite& sprite,
                clad::Transform& transform) {
                auto& renderer { world.resource<clad::Renderer>() };
                renderer.draw(sprite, transform);
            });
    }

    static void present(clad::World& world)
    {
        auto& renderer { world.resource<clad::Renderer>() };
        renderer.present();
    }
};

struct Window {
    inline static const int DEFAULT_WIDTH { 800 };
    inline static const int DEFAULT_HEIGHT { 600 };

    static void build(clad::App& app)
    {
        SDL_Init(SDL_INIT_VIDEO);
        app.emplace_resource<clad::Window>(
            "PONG", DEFAULT_WIDTH, DEFAULT_HEIGHT);
    }
};

struct Ball { };
const float BALL_WIDTH = 8.0;
const float BALL_HEIGHT = 8.0;
const float BALL_INITIAL_X = 395.0;
const float BALL_INITIAL_Y = 295.0;

struct Player { };
const float PADDLE_WIDTH = 12.0;
const float PADDLE_HEIGHT = 72.0;
const float PLAYER_INITIAL_X = 12.0;
const float PLAYER_INITIAL_Y = 295.0;

void startup(clad::World& world)
{
    std::println("startup");

    const clad::Entity ball { world.create() };
    world.emplace<Ball>(ball);
    world.emplace<clad::Sprite>(ball, clad::Color::White,
        clad::Vec2 { .x = BALL_WIDTH, .y = BALL_HEIGHT });
    world.emplace<clad::Transform>(ball, BALL_INITIAL_X, BALL_INITIAL_Y);

    const clad::Entity player { world.create() };
    world.emplace<Player>(player);
    world.emplace<clad::Sprite>(player, clad::Color::White,
        clad::Vec2 { .x = PADDLE_WIDTH, .y = PADDLE_HEIGHT });
    world.emplace<clad::Transform>(player, PLAYER_INITIAL_X, PLAYER_INITIAL_Y);
}

void move_player(clad::World& world)
{
    world.view<Player, clad::Transform>(
        [&world](const clad::Entity /*entity*/, Player& /*player*/,
            clad::Transform& transform) {
            auto& input { world.resource<clad::Input>() };
            if (input.is_key_pressed(clad::Key::Up)) {
                std::println("up key is pressed");
                transform.y -= 1.0;
            }
            if (input.is_key_pressed(clad::Key::Down)) {
                std::println("down key is pressed");
                transform.y += 1.0;
            }
        });
}

void move_ball(clad::World& world)
{
    static const float DELTA = 0.01;
    world.view<Ball, clad::Transform>(
        [&world](const clad::Entity /*entity*/, Ball& /*ball*/,
            clad::Transform& transform) {
            transform.x += DELTA;
            transform.y += DELTA;
        });
}

void shutdown(clad::World& /*world*/) { std::println("shutdown"); }

} // namespace

int main()
{
    clad::App app;
    app.add_systems<clad::Startup>(startup)
        .add_systems<clad::Update>(move_ball, move_player)
        .add_systems<clad::Shutdown>(shutdown)
        .add_plugins(Input {}, Window {}, Render {})
        .build()
        .run();
}
