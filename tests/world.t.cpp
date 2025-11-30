#include "clad/ecs/world.hpp"

#include <vector>

#include "gtest/gtest.h"

#include "clad/math/vec.hpp"
#include "clad/window/window.hpp"

namespace clad::test {

class WorldTest : public testing::Test {
protected:
    World world;
};

TEST_F(WorldTest, SpawnEntity_EntityIsIncremented)
{
    // GIVEN
    // ...

    // WHEN
    const Entity entity1 { world.spawn() };
    const Entity entity2 { world.spawn() };

    // THEN
    EXPECT_EQ(entity1, 0);
    EXPECT_EQ(entity2, entity1 + 1);
}

TEST_F(WorldTest, InsertComponent_ComponentIsPresent)
{
    // GIVEN
    const Entity entity { world.spawn() };
    const Vec2 vec;

    // WHEN
    world.insert_component(entity, vec);
    const std::vector<Vec2>& vecs { world.components<Vec2>() };

    // THEN
    ASSERT_EQ(vecs.size(), 1);
    EXPECT_EQ(vecs[entity], vec);
}

TEST_F(WorldTest, AddResource_ResourceIsPresent)
{
    // GIVEN
    constexpr int width { 800 };
    constexpr int height { 600 };

    // WHEN
    world.emplace_resource<Window>(width, height);
    const auto& window { world.resource<Window>() };

    // THEN
    EXPECT_EQ(window.width, width);
    EXPECT_EQ(window.height, height);
}

TEST_F(WorldTest, AddResource_ExistingResource_ResourceIsUpdated)
{
    // GIVEN
    constexpr int width { 100 };
    constexpr int height { 100 };

    // WHEN
    world.emplace_resource<Window>(width, height);
    const auto& window { world.resource<Window>() };

    // THEN
    EXPECT_EQ(window.width, width);
    EXPECT_EQ(window.height, height);
}

TEST_F(WorldTest, View_ComponentsAreUpdated)
{
    // GIVEN
    constexpr Vec2 viewed_vec { .x = 100.0, .y = 100.0 };

    /// WHEN
    world.view<Vec2>(
        [viewed_vec](const Entity /*entity*/, Vec2& vec) { vec = viewed_vec; });
    const std::vector<Vec2>& vecs { world.components<Vec2>() };

    // THEN
    for (const auto& vec : vecs) {
        EXPECT_EQ(vec, viewed_vec);
    }
}

} // namespace clad::test
