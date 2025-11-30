#ifndef CLAD_WORLD_HPP
#define CLAD_WORLD_HPP

#include <cassert>
#include <stdexcept>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "clad/std/any.hpp"

#include "entity.hpp"
#include "storage.hpp"
#include "tick.hpp"

namespace clad {

/// A specialized container for storing, querying, and interacting with
/// entities, components, and resources.
class World {
public:
    /// Spawns a new `::Entity` into this world.
    ///
    /// \return A new entity identifier.
    Entity spawn() noexcept
    {
        ++m_tick;
        return m_next_entity++;
    }

    /// Inserts a component into this world and associates it with an
    /// `::Entity`.
    ///
    /// \tparam T The type of component to insert.
    /// \param entity The `::entity` to associate the component with.
    /// \param component The component to insert.
    template <typename T>
    void insert_component(const Entity entity, const T& component)
    {
        Storage<T>& components { this->components<T>() };
        components.insert(entity, { m_tick, m_tick }, component);
        ++m_tick;
    }

    /// Inserts a new component into this `::world` constructed in-place with
    /// the given `args` and associates it with an `::entity`.
    ///
    /// \tparam T The type of component to insert.
    /// \tparam Args The pack of component constructor parameter types.
    /// \param entity The `::entity` to associate the component with.
    /// \param args The arguments to forward to the constructor of the
    ///     component.
    template <typename T, typename... Args>
    void emplace_component(const Entity entity, Args&&... args)
    {
        m_components.emplace(
            entity, { m_tick, m_tick }, std::forward<Args>(args)...);
        ++m_tick;
    }

    /// Inserts a new resource into this `::world` constructed in-place with
    /// the given `args`.
    ///
    /// Resources are unique data types managed by the `::world`. They are
    /// similar to singletons in that only one instance can exist at any time;
    /// however, resources do not have global state. Their lifetimes are tied
    /// to the `::world` that owns them.
    ///
    /// \tparam T The type of resource to insert.
    /// \tparam Args The pack of resource constructor parameter types.
    /// \param args The arguments to forward to the constructor of the
    ///     resource.
    template <typename T, typename... Args>
    void emplace_resource(Args&&... args)
    {
        const auto type_id { std::type_index(typeid(T)) };
        m_resources.emplace(std::piecewise_construct,
            std::forward_as_tuple(type_id),
            std::forward_as_tuple(
                std::in_place_type_t<T> {}, std::forward<Args>(args)...));
        ++m_tick;
    }

    /// Clears all entities from this `::world`.
    void clear() noexcept
    {
        m_next_entity = 0;
        m_components.clear();
        ++m_tick;
    }

    /// Returns this `::world`'s component collection of the given type.
    ///
    /// \tparam T The type of component collection to return.
    /// \return A reference to the component collection.
    template <typename T>
    Storage<T>& components() noexcept
    {
        const auto type_id { std::type_index(typeid(T)) };
        const auto it { m_components.find(type_id) };
        assert(it != m_components.end());
        return any_cast<T>(it->second);
    }

    /// Returns a resource from this `::world`.
    ///
    /// \tparam T The type of resource to return.
    /// \return A reference to the resource.
    /// \throws std::out_of_range if the resource is not found.
    template <typename T>
    T& resource()
    {
        const auto type_id { std::type_index(typeid(T)) };
        const auto it { m_resources.find(type_id) };

        if (it == m_resources.end()) {
            throw std::out_of_range(
                "Resource '" + std::string(type_id.name()) + "' not found");
        }

        return any_cast<T>(it->second);
    }

    /// Invokes a function on each `::entity` associated with the given types
    /// of components.
    ///
    /// \tparam T The types of components that each `::entity` must be
    ///     associated with.
    /// \tparam Fn The type of function to invoke.
    /// \param fn The function to invoke for each matching `::entity`.
    template <typename... T, typename Fn>
    void view(Fn&& fn)
    {
        auto& first_components {
            components<std::tuple_element_t<0, std::tuple<T...>>>()
        };
        for (const Entity entity : first_components.ids()) {
            if ((components<T>().contains(entity) && ...)) {
                std::forward<Fn>(fn)(entity, components<T>()[entity]...);
            }
        }
    }

private:
    Entity m_next_entity { 0 };
    Tick m_tick;
    std::unordered_map<std::type_index, any> m_components;
    std::unordered_map<std::type_index, any> m_resources;
};

} // namespace clad

#endif // !CLAD_WORLD_HPP
