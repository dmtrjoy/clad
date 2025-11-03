#include "clad/app/app.hpp"

#include "gtest/gtest.h"

namespace clad::test {

namespace {

    struct FooPlugin {
        static void build(App& /*app*/) { assert(false); }
    };

    struct BarPlugin {
        static void build(App& /*app*/) { assert(false); }
    };

} // namespace

TEST(AppTest, AddPlugins_TransferablePlugins_PluginsArePresent)
{
    // GIVEN
    App app;
    BarPlugin bar {};

    // WHEN
    app.add_plugins(FooPlugin {}, std::move(bar)); // NOLINT(*-move-const-arg)

    // THEN
    app.plugin<FooPlugin>();
    app.plugin<BarPlugin>();
}

TEST(AppTest, AddPlugins_PluginNotBuilt)
{
    // GIVEN
    App app;

    // WHEN/THEN
    app.add_plugins(FooPlugin {});
}

TEST(AppTest, AddPlugins_DuplicatePlugins_ProgramCrashes)
{
    // GIVEN
    App app;

    // WHEN/THEN
    EXPECT_DEATH(app.add_plugins(FooPlugin {}, FooPlugin {}),
        "Assertion failed: (m_plugins.find(type_id) == m_plugins.end())*");
}

// TEST(AppTest, AddPlugins_MissingBuildMemberFunction_CompilationFails)
// {
//     // GIVEN
//     App app;
//     struct EmptyPlugin { };
//
//     // WHEN/THEN
//     app.add_plugins(EmptyPlugin {});
// }

// TEST(AppTest, AddPlugins_LValuePlugin_CompilationFails)
// {
//     // GIVEN
//     App app;
//     CounterPlugin counter {};
//
//     // WHEN/THEN
//     app.add_plugins(counter);
// }

// TEST(AppTest, AddPlugins_ConstPlugin_CompilationFails)
// {
//     // GIVEN
//     App app;
//     const CounterPlugin counter {};
//
//     // WHEN/THEN
//     app.add_plugins(std::move(counter));
// }

// TEST(AppTest, AddPlugins_VolatilePlugin_CompilationFails)
// {
//     // GIVEN
//     App app;
//     volatile CounterPlugin counter {};
//
//     // WHEN/THEN
//     app.add_plugins(std::move(counter));
// }

} // namespace clad::test
