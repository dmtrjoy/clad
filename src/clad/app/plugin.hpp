#ifndef CLAD_PLUGIN_HPP
#define CLAD_PLUGIN_HPP

#include <concepts>
#include <type_traits>

namespace clad {

class App;

template <typename T>
concept Plugin = requires(std::remove_cvref_t<T>& plugin, App& app) {
    { plugin.build(app) } -> std::same_as<void>;
};

template <typename T>
concept TransferablePlugin
    = Plugin<T> && !std::is_const_v<std::remove_reference_t<T>>
    && !std::is_lvalue_reference_v<T>
    && !std::is_volatile_v<std::remove_reference_t<T>>;

} // namespace clad

#endif // !CLAD_PLUGIN_HPP
