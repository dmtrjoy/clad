#include "clad/app/app.hpp"

#include "gtest/gtest.h"

#include "clad/app/event.hpp"
#include "clad/ecs/world.hpp"

namespace clad::test {

namespace {

    void test_system(World& world) { }

} // namespace

TEST(AppTest, AddSystem)
{
    // GIVEN
    App app;

    // WHEN
    app.schedule(Event::Startup, test_system).run();
}

} // namespace clad::test
