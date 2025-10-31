#ifndef CLAD_FEATURE_HPP
#define CLAD_FEATURE_HPP

#include <concepts>

namespace clad {

class App;

template <typename T>
concept Feature = requires(T feature, App& app) {
    { feature.build(app) } -> std::same_as<void>;
};

} // namespace clad

#endif // !CLAD_FEATURE_HPP
