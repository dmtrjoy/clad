#include "clad/app/schedule.hpp"

#include "gtest/gtest.h"

#include "clad/ecs/entity.hpp"
#include "clad/ecs/world.hpp"

namespace clad::test {

namespace {

    struct test_component {
        bool has_run = false;
    };

    void create(World& world)
    {
        Entity entity = world.create();
        test_component component { .has_run = true };
        world.insert(entity, component);
    }

    void create_two_entities(World& world)
    {
        Entity entity1 = world.create();
        Entity entity2 = world.create();
        test_component component { .has_run = true };
        world.insert(entity1, component);
        world.insert(entity2, component);
    }

} // namespace

TEST(ScheduleTest, Run_SystemsRanSequentially)
{
    // GIVEN
    Schedule schedule;
    schedule.add(create, create_two_entities);

    World world;

    // WHEN
    schedule.run(world);

    // THEN
    sparse_set<test_component> components = world.components<test_component>();
    ASSERT_EQ(components.size(), 3);
}

} // namespace clad::test
