#ifndef CLAD_WINDOW_HPP
#define CLAD_WINDOW_HPP

#include <memory>
#include <string>

class renderer;
struct SDL_Window;

namespace clad {

/// A resizable window with a title and dimensions.
class window {
public:
    /// Constructs a blank `::window`.
    ///
    /// \param title A title displayed at the top of the window.
    /// \param width The width of the window in pixels.
    /// \param height The height of the window in pixels.
    window(const std::string& title, int width, int height) noexcept;

    window(const window& other) noexcept = delete;

    /// Constructs a `::window` by moving the contents of another `::window`
    /// into this one.
    ///
    /// \param other The object to move from. Left in a valid but unspecified
    ///     state.
    window(window&& other) noexcept = default;

    window& operator=(const window& other) noexcept = delete;

    /// Moves the contents of another `::window` into this one.
    ///
    /// \param other The object to move from. Left in a valid but unspecified
    ///     state.
    /// \return A reference to this object.
    window& operator=(window&& other) noexcept = default;

    /// Destroys a `::window`.
    ~window() noexcept;

    auto operator<=>(const window&) const = default;

private:
    class impl;
    std::unique_ptr<impl> m_pimpl;

    friend class renderer;
    [[nodiscard]] SDL_Window* native() const noexcept;
};

} // namespace clad

#endif // !CLAD_WINDOW_HPP
