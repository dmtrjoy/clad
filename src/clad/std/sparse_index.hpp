#ifndef CLAD_SPARSE_INDEX_HPP
#define CLAD_SPARSE_INDEX_HPP

#include <concepts>
#include <vector>

#include "types.hpp"

namespace clad {

template <typename T, std::unsigned_integral IdType = u32>
class sparse_index {
public:
    using value_type = T;
    using id_type = IdType;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;

    void insert(const id_type id)
    {
        assert(id != s_tombstone);

        if (contains(id)) {
            m_dense_ids[m_sparse[id]] = id;
            return;
        }

        if (id >= m_sparse.size()) {
            m_sparse.resize(id + 1, s_tombstone);
        }

        m_sparse[id] = m_dense_ids.size();
        m_dense_ids.push_back(id);
    }

    /// Checks whether there is an element with an identifier equivalent to `id`
    /// in the container.
    ///
    /// \param id The `id` of the element to search for.
    /// \return `true` if a matching element is found; `false` otherwise.
    [[nodiscard]] bool contains(const id_type id) const noexcept
    {
        assert(id != s_tombstone);

        if (id >= m_sparse.size()) {
            return false;
        }

        const id_type dense_id { m_sparse[id] };
        return dense_id != s_tombstone && m_dense_ids[dense_id] == id;
    };

private:
    static constexpr id_type s_tombstone = std::numeric_limits<id_type>().max();
    std::vector<id_type> m_sparse;
    std::vector<id_type> m_dense_ids;
};

} // namespace clad

#endif // !CLAD_SPARSE_INDEX_HPP
