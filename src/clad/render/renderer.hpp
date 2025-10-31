#ifndef CLAD_RENDERER_HPP
#define CLAD_RENDERER_HPP

#include <memory>

#include "clad/sprite/sprite.hpp"
#include "clad/sprite/transform.hpp"
#include "clad/window/window.hpp"

namespace clad {

class Renderer {
public:
    explicit Renderer(Window& window) noexcept;

    void clear() noexcept;

    void draw(const Sprite& sprite, const Transform& transform) noexcept;

    void present() noexcept;

    ~Renderer() noexcept;

private:
    class Impl;
    std::unique_ptr<Impl> m_pimpl;
};

} // namespace clad

#endif // !CLAD_RENDERER_HPP
