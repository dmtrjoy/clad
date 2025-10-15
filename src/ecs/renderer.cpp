#include "renderer.hpp"

#include <cassert>
#include <memory>

#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

#include "sprite.hpp"
#include "transform.hpp"
#include "window.hpp"

namespace clad {

class renderer::impl {
public:
    explicit impl(window& window)
        : m_renderer(SDL_CreateRenderer(window.native(), ""))
    {
        assert(m_renderer != nullptr);
    }

    void clear() noexcept { SDL_RenderClear(m_renderer); }

    void draw(const sprite& sprite, const transform& transform) noexcept
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        clear();

        SDL_FRect rect { transform.x, transform.y, sprite.size.x,
            sprite.size.y };
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(m_renderer, &rect);

        SDL_RenderPresent(m_renderer);
    }

private:
    SDL_Renderer* m_renderer;
};

renderer::renderer(window& window) noexcept
    : m_pimpl(std::make_unique<impl>(window))
{
}

renderer::~renderer() noexcept = default;

void renderer::clear() noexcept { m_pimpl->clear(); }

void renderer::draw(const sprite& sprite, const transform& transform) noexcept
{
    m_pimpl->draw(sprite, transform);
}

} // namespace clad
