#include "input.hpp"

#include <memory>
#include <print>
#include <unordered_map>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keycode.h"

namespace clad {

class Input::Impl {
public:
    [[nodiscard]] bool is_key_pressed(const Key key)
    {
        if (key == Key::Up && m_pressed[SDLK_UP]) {
            return true;
        }
        if (key == Key::Down && m_pressed[SDLK_DOWN]) {
            return true;
        }
        if (key == Key::Left && m_pressed[SDLK_LEFT]) {
            return true;
        }
        if (key == Key::Right && m_pressed[SDLK_RIGHT]) {
            return true;
        }
        return false;
    }

    void poll()
    {
        m_just_pressed.clear();
        m_just_released.clear();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                m_quit = true;
            }

            if (event.type == SDL_EVENT_KEY_DOWN) {
                m_pressed[event.key.key] = true;
                if (!event.key.repeat) {
                    m_just_pressed[event.key.key] = true;
                }
            }

            if (event.type == SDL_EVENT_KEY_UP) {
                m_pressed[event.key.key] = false;
                m_just_released[event.key.key] = true;
            }
        }
    }

    [[nodiscard]] bool quit() const { return m_quit; }

private:
    std::unordered_map<SDL_Keycode, bool> m_pressed;
    std::unordered_map<SDL_Keycode, bool> m_just_pressed;
    std::unordered_map<SDL_Keycode, bool> m_just_released;
    bool m_quit { false };
};

Input::Input()
    : m_pimpl(std::make_unique<Impl>())
{
}

Input::~Input() = default;

bool Input::is_key_pressed(const Key key)
{
    return m_pimpl->is_key_pressed(key);
}

void Input::poll() { m_pimpl->poll(); }

bool Input::quit() const { return m_pimpl->quit(); }

} // namespace clad
