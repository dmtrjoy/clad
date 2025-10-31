#ifndef CLAD_WINDOW_HPP
#define CLAD_WINDOW_HPP

#include <memory>
#include <string>

class Renderer;
struct SDL_Window;

namespace clad {

/// A resizable window with a title and dimensions.
class Window {
public:
    /// Constructs a blank `::window`.
    ///
    /// \param title A title displayed at the top of the window.
    /// \param width The width of the window in pixels.
    /// \param height The height of the window in pixels.
    Window(const std::string& title, int width, int height) noexcept;

    Window(const Window& other) noexcept = delete;

    /// Constructs a `::window` by moving the contents of another `::window`
    /// into this one.
    ///
    /// \param other The object to move from. Left in a valid but unspecified
    ///     state.
    Window(Window&& other) noexcept = default;

    Window& operator=(const Window& other) noexcept = delete;

    /// Moves the contents of another `::window` into this one.
    ///
    /// \param other The object to move from. Left in a valid but unspecified
    ///     state.
    /// \return A reference to this object.
    Window& operator=(Window&& other) noexcept = default;

    /// Destroys a `::window`.
    ~Window() noexcept;

    auto operator<=>(const Window&) const = default;

private:
    class Impl;
    std::unique_ptr<Impl> m_pimpl;

    friend class Renderer;
    [[nodiscard]] SDL_Window* native() const noexcept;
};

} // namespace clad

#endif // !CLAD_WINDOW_HPP
