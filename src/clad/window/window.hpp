#ifndef CLAD_WINDOW_HPP
#define CLAD_WINDOW_HPP

#include <string_view>

namespace clad {

/// A resizable window with a title and dimensions.
struct Window {
    std::string_view title; /// A title displayed at the top of the window.
    int width; /// The width of the window in pixels.
    int height; /// The height of the window in pixels.
};

} // namespace clad

#endif // !CLAD_WINDOW_HPP
