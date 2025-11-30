#ifndef CLAD_STORAGE_HPP
#define CLAD_STORAGE_HPP

#include <utility>
#include <vector>

#include "clad/std/sparse_index.hpp"

#include "component.hpp"
#include "entity.hpp"

namespace clad {

template <typename T>
class Storage {
public:
    void insert(
        const Entity entity, ComponentMetadata&& metadata, const T& component)
    {
        m_component_index.insert(entity);
        m_component_metadata.push_back(std::move(metadata));
        m_components.push_back(component);
    }

    template <typename... Args>
    void emplace(
        const Entity entity, ComponentMetadata&& metadata, Args&&... args)
    {
        m_component_index.insert(entity);
        m_component_metadata.push_back(std::move(metadata));
        m_components.emplace_back(std::forward<Args>(args)...);
    }

    std::vector<T>& components() noexcept { return m_components; }

    void clear() noexcept
    {
        m_component_index.clear();
        m_component_metadata.clear();
        m_components.clear();
    }

private:
    sparse_index<T> m_component_index;
    std::vector<T> m_component_metadata;
    std::vector<T> m_components;
};

} // namespace clad

#endif // !CLAD_STORAGE_HPP
