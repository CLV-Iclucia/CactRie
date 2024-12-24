//
// Created by creeper on 12/24/24.
//

#ifndef LRU_CACHE_H
#define LRU_CACHE_H
#include <unordered_map>
#include <vector>
#include <optional>
#include <functional>

namespace mystl {
template <typename Key, typename Value, typename Compare = std::equal_to<Key>>
class lru_cache {
public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<Key, Value>;
    using size_type = std::size_t;

    explicit lru_cache(size_type capacity, Compare compare = Compare())
        : capacity_(capacity), compare_(compare) {}

    void insert(const key_type& key, const mapped_type& value) {
        auto it = m_cache_map.find(key);
        if (it != m_cache_map.end()) {
            auto pos = it->second;
            m_cache[pos].second = value;
            touch(pos);
        } else {
            if (m_cache.size() >= capacity_) {
                evict();
            }
            m_cache.emplace_back(key, value);
            m_cache_map[key] = m_cache.size() - 1;
        }
    }

    std::optional<mapped_type> find(const key_type& key) {
        auto it = m_cache_map.find(key);
        if (it == m_cache_map.end())
            return std::nullopt;
        auto pos = it->second;
        touch(pos);
        return m_cache[pos].second;
    }

    bool contains(const key_type& key) const {
        return m_cache_map.contains(key)  ;
    }

    [[nodiscard]] size_type size() const noexcept {
        return m_cache.size();
    }

    [[nodiscard]] bool empty() const noexcept {
        return m_cache.empty();
    }

private:
    size_type capacity_;
    Compare compare_;
    std::vector<value_type> m_cache{};
    std::unordered_map<key_type, size_type, std::hash<key_type>, Compare> m_cache_map{};

    void touch(size_type pos) {
        value_type entry = std::move(m_cache[pos]);
        m_cache.erase(m_cache.begin() + pos);
        m_cache.push_back(std::move(entry));

        for (size_type i = pos; i < m_cache.size(); ++i) {
            m_cache_map[m_cache[i].first] = i;
        }
    }

    void evict() {
        const key_type& key_to_remove = m_cache.front().first;
        m_cache.erase(m_cache.begin());
        m_cache_map.erase(key_to_remove);

        for (size_type i = 0; i < m_cache.size(); ++i) {
            m_cache_map[m_cache[i].first] = i;
        }
    }
};

}
#endif //LRU_CACHE_H
