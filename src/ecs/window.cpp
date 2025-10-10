#include "window.hpp"

#include <cassert>
#include <memory>
#include <string>

#include "SDL3/SDL_video.h"

namespace clad {

class window::impl {
public:
    impl(const std::string& title, const int width, const int height) noexcept
        : m_window(SDL_CreateWindow(
              title.c_str(), width, height, SDL_WINDOW_RESIZABLE))
    {
        assert(m_window != nullptr);
    }

    impl(const impl& other) noexcept = delete;
    impl(impl&& other) noexcept = default;
    impl& operator=(const impl& other) noexcept = delete;
    impl& operator=(impl&& other) noexcept = default;

    ~impl()
    {
        assert(m_window != nullptr);
        SDL_DestroyWindow(m_window);
    }

private:
    SDL_Window* m_window { nullptr };
};

window::window(
    const std::string& title, const int width, const int height) noexcept
    : m_pimpl(std::make_unique<impl>(title, width, height))
{
}

window::~window() noexcept = default;

} // namespace clad
