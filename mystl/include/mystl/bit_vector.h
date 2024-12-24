//
// Created by creeper on 12/16/24.
//

#ifndef MYSTL_BIT_VECTOR_H
#define MYSTL_BIT_VECTOR_H
#include <iostream>
#include <vector>
#include <bitset>
#include <cassert>
#include <variant>
#include <cstdint>

namespace mystl {
class bit_vector {
  private:
    static constexpr size_t SOO_THRESHOLD = 64 * 3; // Threshold for small object optimization
    std::variant<std::bitset<SOO_THRESHOLD>, std::vector<uint64_t>> data;
    size_t size_;

  public:
    bit_vector() = default;
    explicit bit_vector(size_t size)
      : size_(size) {
      if (size > SOO_THRESHOLD) {
        data = std::vector<uint64_t>((size + 63) >> 6, 0); // 64 bits per uint64_t
      }
      else
        data = std::bitset<SOO_THRESHOLD>();
    }

    explicit bit_vector(size_t size, bool value)
      : size_(size) {
      if (size > SOO_THRESHOLD) {
        data = std::vector<uint64_t>((size + 63) >> 6, value ? ~0ull : 0);
      }
      else
        data = std::bitset<SOO_THRESHOLD>(value ? ~0ull : 0);
    }

    static bit_vector empty_set(size_t size) {
      return bit_vector(size, false);
    }

    static bit_vector full_set(size_t size) {
      return bit_vector(size, true);
    }

    bit_vector(const bit_vector&other)
      : size_(other.size_) {
      if (std::holds_alternative<std::vector<uint64_t>>(other.data)) {
        data = std::get<std::vector<uint64_t>>(other.data);
      }
      else
        data = std::get<std::bitset<SOO_THRESHOLD>>(other.data);
    }

    bit_vector& operator=(const bit_vector&other) {
      if (this != &other) {
        size_ = other.size_;
        if (std::holds_alternative<std::vector<uint64_t>>(other.data))
          data = std::get<std::vector<uint64_t>>(other.data);
        else
          data = std::get<std::bitset<SOO_THRESHOLD>>(other.data);
      }
      return *this;
    }

    bit_vector(bit_vector&&other) noexcept
      : size_(other.size_) {
      if (std::holds_alternative<std::vector<uint64_t>>(other.data))
        data = std::move(std::get<std::vector<uint64_t>>(other.data));
      else
        data = std::get<std::bitset<SOO_THRESHOLD>>(other.data);
    }

    bit_vector& operator=(bit_vector&&other) noexcept {
      if (this != &other) {
        size_ = other.size_;
        if (std::holds_alternative<std::vector<uint64_t>>(other.data))
          data = std::move(std::get<std::vector<uint64_t>>(other.data));
        else
          data = std::get<std::bitset<SOO_THRESHOLD>>(other.data);
      }
      return *this;
    }

    bool operator[](size_t index) const {
      if (std::holds_alternative<std::vector<uint64_t>>(data)) {
        size_t wordIndex = index / 64;
        size_t bitIndex = index % 64;
        return (std::get<std::vector<uint64_t>>(data)[wordIndex] >> bitIndex) & 1;
      }
      return (std::get<std::bitset<SOO_THRESHOLD>>(data)[index]);
    }

    bit_vector& operator&=(const bit_vector&other) {
      if (size_ != other.size_) {
        throw std::invalid_argument("bit_vectors must be of the same size for bitwise operation");
      }
      if (std::holds_alternative<std::vector<uint64_t>>(data) &&
        std::holds_alternative<std::vector<uint64_t>>(other.data)) {
        for (size_t i = 0; i < std::get<std::vector<uint64_t>>(data).size(); ++i)
          std::get<std::vector<uint64_t>>(data)[i] &= std::get<std::vector<uint64_t>>(other.data)[i];
      }
      else
        std::get<std::bitset<SOO_THRESHOLD>>(data) &= std::get<std::bitset<SOO_THRESHOLD>>(other.data);
      return *this;
    }

    bit_vector operator&(const bit_vector&other) const {
      bit_vector result(size_);
      result = *this;
      result &= other;
      return result;
    }

    bit_vector& operator|=(const bit_vector&other) {
      if (size_ != other.size_)
        throw std::invalid_argument("bit_vectors must be of the same size for bitwise operation");

      if (std::holds_alternative<std::vector<uint64_t>>(data)) {
        assert(std::holds_alternative<std::vector<uint64_t>>(other.data));
        for (size_t i = 0; i < std::get<std::vector<uint64_t>>(data).size(); ++i)
          std::get<std::vector<uint64_t>>(data)[i] |= std::get<std::vector<uint64_t>>(other.data)[i];
      }
      else
        std::get<std::bitset<SOO_THRESHOLD>>(data) |= std::get<std::bitset<SOO_THRESHOLD>>(other.data);
      return *this;
    }

    bit_vector operator|(const bit_vector&other) const {
      bit_vector result(size_);
      result = *this;
      result |= other;
      return result;
    }

    bit_vector& operator^=(const bit_vector&other) {
      if (size_ != other.size_) {
        throw std::invalid_argument("bit_vectors must be of the same size for bitwise operation");
      }
      if (std::holds_alternative<std::vector<uint64_t>>(data) &&
        std::holds_alternative<std::vector<uint64_t>>(other.data)) {
        for (size_t i = 0; i < std::get<std::vector<uint64_t>>(data).size(); ++i)
          std::get<std::vector<uint64_t>>(data)[i] ^= std::get<std::vector<uint64_t>>(other.data)[i];
      }
      else
        std::get<std::bitset<SOO_THRESHOLD>>(data) ^= std::get<std::bitset<SOO_THRESHOLD>>(other.data);
      return *this;
    }

    bit_vector operator^(const bit_vector&other) const {
      bit_vector result(size_);
      result = *this;
      result ^= other;
      return result;
    }

    bit_vector operator~() const {
      bit_vector result(size_);
      if (std::holds_alternative<std::vector<uint64_t>>(data))
        for (size_t i = 0; i < std::get<std::vector<uint64_t>>(data).size(); ++i)
          std::get<std::vector<uint64_t>>(result.data)[i] = ~std::get<std::vector<uint64_t>>(data)[i];
      else
        std::get<std::bitset<SOO_THRESHOLD>>(result.data) = ~std::get<std::bitset<SOO_THRESHOLD>>(data);
      return result;
    }

    bool operator==(const bit_vector&other) const {
      if (size_ != other.size_)
        return false;
      if (std::holds_alternative<std::vector<uint64_t>>(data) &&
        std::holds_alternative<std::vector<uint64_t>>(other.data)) {
        return std::get<std::vector<uint64_t>>(data) == std::get<std::vector<uint64_t>>(other.data);
      }
      for (size_t i = 0; i < size_; ++i)
        if ((*this)[i] != other[i])
          return false;
      return true;
    }

    void place(size_t index) {
      if (std::holds_alternative<std::vector<uint64_t>>(data)) {
        size_t wordIndex = index / 64;
        size_t bitIndex = index % 64;
        std::get<std::vector<uint64_t>>(data)[wordIndex] |= 1ull << bitIndex;
      }
      else
        std::get<std::bitset<SOO_THRESHOLD>>(data)[index] = true;
    }

    bit_vector& unset(size_t index) {
      if (std::holds_alternative<std::vector<uint64_t>>(data)) {
        size_t wordIndex = index / 64;
        size_t bitIndex = index % 64;
        std::get<std::vector<uint64_t>>(data)[wordIndex] &= ~(1ull << bitIndex);
      }
      else
        std::get<std::bitset<SOO_THRESHOLD>>(data)[index] = false;
      return *this;
    }

  class iterator {
      const bit_vector& bv;
      size_t pos;
      uint64_t current_word;
      size_t word_index;

      public:
      iterator(const bit_vector& bv, size_t start_pos)
        : bv(bv), pos(start_pos), current_word(0), word_index(0) {
        advance_to_next_set_bit();
      }

      iterator& operator++() {
        advance_to_next_set_bit();
        return *this;
      }

      size_t operator*() const { return pos; }

      bool operator!=(const iterator& other) const { return pos != other.pos; }

      private:
      void advance_to_next_set_bit() {
        while (pos < bv.size()) {
          if (std::holds_alternative<std::vector<uint64_t>>(bv.data)) {
            const auto& vec = std::get<std::vector<uint64_t>>(bv.data);

            if (current_word == 0) {
              if (word_index >= vec.size()) {
                pos = bv.size();
                return;
              }
              current_word = vec[word_index++];
            }

            if (current_word) {
              size_t lowbit_pos = __builtin_ctzll(current_word);
              pos = (word_index - 1) * 64 + lowbit_pos;
              current_word &= current_word - 1;
              if (pos < bv.size()) return;
            }
          } else {
            const auto& bs = std::get<std::bitset<SOO_THRESHOLD>>(bv.data);
            while (pos < bv.size() && !bs.test(pos)) ++pos;
            if (pos < bv.size()) return;
          }
        }

        pos = bv.size();
      }
    };

    [[nodiscard]] bool is_subset_of(const bit_vector& other) const {
      for (size_t i = 0; i < size_; ++i)
        if ((*this)[i] && !other[i])
          return false;
      return true;
    }

  [[nodiscard]] iterator begin() const { return {*this, 0}; }
  [[nodiscard]] iterator end() const { return {*this, size_}; }

    [[nodiscard]] size_t size() const {
      return size_;
    }
};
}
#endif //MYSTL_BIT_VECTOR_H
