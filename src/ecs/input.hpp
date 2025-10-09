#ifndef CLAD_INPUT_HPP
#define CLAD_INPUT_HPP

#include <memory>

#include "types.hpp"

namespace clad {

enum class key : u8 {
    left,
    right,
    up,
    down,
    a,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n
};

class input {
public:
    input();
    ~input();

    void add_action();
    [[nodiscard]] bool is_key_pressed(key key);
    void poll();
    [[nodiscard]] bool quit() const;

private:
    class impl;
    std::unique_ptr<impl> m_pimpl;
};

} // namespace clad

#endif // !CLAD_INPUT_HPP
