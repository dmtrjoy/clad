#include "clad/app/schedule.hpp"

#include "gtest/gtest.h"
#include <vector>

#include "clad/ecs/entity.hpp"
#include "clad/ecs/world.hpp"

namespace clad::test {

namespace {

    struct TestComponent {
        bool has_run = false;
    };

    void spawn(World& world)
    {
        Entity entity = world.spawn();
        TestComponent component { .has_run = true };
        world.insert_component(entity, component);
    }

    void spawn_two_entities(World& world)
    {
        Entity entity1 = world.spawn();
        Entity entity2 = world.spawn();
        TestComponent component { .has_run = true };
        world.insert_component(entity1, component);
        world.insert_component(entity2, component);
    }

} // namespace

TEST(ScheduleTest, Run_SystemsRanSequentially)
{
    // GIVEN
    Schedule schedule;
    schedule.add_systems(spawn, spawn_two_entities);

    World world;

    // WHEN
    schedule.run(world);

    // THEN
    const std::vector<TestComponent>& components {
        world.components<TestComponent>()
    };
    EXPECT_EQ(components.size(), 3);
}

} // namespace clad::test
