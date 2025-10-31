#include "renderer.hpp"

#include <cassert>
#include <memory>

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

#include "clad/sprite/sprite.hpp"
#include "clad/sprite/transform.hpp"
#include "clad/window/window.hpp"

namespace clad {

class Renderer::Impl {
public:
    explicit Impl(Window& window)
        : m_renderer(SDL_CreateRenderer(window.native(), ""))
    {
        assert(m_renderer != nullptr);
    }

    void clear() noexcept
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);
    }

    void draw(const Sprite& sprite, const Transform& transform) noexcept
    {
        SDL_FRect rect { transform.x, transform.y, sprite.size.x,
            sprite.size.y };
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(m_renderer, &rect);
    }

    void present() noexcept { SDL_RenderPresent(m_renderer); }

private:
    SDL_Renderer* m_renderer;
};

Renderer::Renderer(Window& window) noexcept
    : m_pimpl(std::make_unique<Impl>(window))
{
}

Renderer::~Renderer() noexcept = default;

void Renderer::clear() noexcept { m_pimpl->clear(); }

void Renderer::draw(const Sprite& sprite, const Transform& transform) noexcept
{
    m_pimpl->draw(sprite, transform);
}

void Renderer::present() noexcept { m_pimpl->present(); }

} // namespace clad
