#ifndef CLAD_RENDERER_HPP
#define CLAD_RENDERER_HPP

#include <memory>

#include "sprite.hpp"
#include "transform.hpp"
#include "window.hpp"

namespace clad {

class renderer {
public:
    explicit renderer(window& window) noexcept;

    void clear() noexcept;

    void draw(const sprite& sprite, const transform& transform) noexcept;

    ~renderer() noexcept;

private:
    class impl;
    std::unique_ptr<impl> m_pimpl;
};

} // namespace clad

#endif // !CLAD_RENDERER_HPP
