#ifndef CLAD_MESSAGES_HPP
#define CLAD_MESSAGES_HPP

#include <vector>

namespace clad {

template <typename T>
class Messages {
public:
    void send(T message);

private:
    std::vector<T> m_buffer;
    std::vector<T> m_prev_buffer;
};

} // namespace clad

#endif // !CLAD_MESSAGES_HPP
