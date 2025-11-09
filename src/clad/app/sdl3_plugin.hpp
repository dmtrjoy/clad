#ifndef SDL3_PLUGIN
#define SDL3_PLUGIN

#include <unordered_map>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"

#include "app.hpp"

namespace clad {

const static std::unordered_map<SDL_EventType, int> test {};

struct Sdl3Plugin {
    static void build(App& app) { app.runner() = runner; }

    static void runner(App& app)
    {
        assert(SDL_Init(SDL_INIT_VIDEO));

        app.startup();

        while (!app.quit()) {
            SDL_Event event;
            // todo: add back basic app event system
            // basically sdl3 events need to be translated into
            // app events. this allows us to essentially support
            // any backend as long as it can translate into
            // the app state/event types.
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    app.request_quit();
                }
            }
        }

        app.tick();

        app.shutdown();

        SDL_Quit();
    }
};

} // namespace clad

#endif // !SDL3_PLUGIN
