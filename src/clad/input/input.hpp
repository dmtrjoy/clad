#ifndef CLAD_INPUT_HPP
#define CLAD_INPUT_HPP

#include <memory>

#include "clad/std/types.hpp"

namespace clad {

enum class Key : u8 {
    Left,
    Right,
    Up,
    Down,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N
};

class Input {
public:
    Input();
    ~Input();

    void add_action();
    [[nodiscard]] bool is_key_pressed(Key key);
    void poll();
    [[nodiscard]] bool quit() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_pimpl;
};

} // namespace clad

#endif // !CLAD_INPUT_HPP
