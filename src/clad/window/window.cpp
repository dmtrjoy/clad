#include "window.hpp"

#include <cassert>
#include <memory>
#include <string>

#include "SDL3/SDL_video.h"

namespace clad {

class Window::Impl {
public:
    Impl(const std::string& title, const int width, const int height) noexcept
        : m_window(SDL_CreateWindow(
              title.c_str(), width, height, SDL_WINDOW_RESIZABLE))
    {
        assert(m_window != nullptr);
    }

    Impl(const Impl& other) noexcept = delete;
    Impl(Impl&& other) noexcept = default;
    Impl& operator=(const Impl& other) noexcept = delete;
    Impl& operator=(Impl&& other) noexcept = default;

    ~Impl() noexcept
    {
        assert(m_window != nullptr);
        SDL_DestroyWindow(m_window);
    }

    [[nodiscard]] SDL_Window* native() const noexcept { return m_window; }

private:
    SDL_Window* m_window { nullptr };
};

Window::Window(
    const std::string& title, const int width, const int height) noexcept
    : m_pimpl(std::make_unique<Impl>(title, width, height))
{
}

Window::~Window() noexcept = default;

SDL_Window* Window::native() const noexcept { return m_pimpl->native(); }

} // namespace clad
