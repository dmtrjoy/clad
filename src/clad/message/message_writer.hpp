#ifndef CLAD_MESSAGE_WRITER_HPP
#define CLAD_MESSAGE_WRITER_HPP

#include "messages.hpp"

namespace clad {

template <typename T>
class MessageWriter {
public:
    void write(T message);

private:
    Messages<T> m_messages;
};

} // namespace clad

#endif // !CLAD_MESSAGE_WRITER_HPP
