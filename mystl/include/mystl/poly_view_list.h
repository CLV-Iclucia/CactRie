//
// Created by creeper on 12/31/24.
//

#ifndef POLY_VIEW_LIST_H
#define POLY_VIEW_LIST_H
#include <list>
#include "observer_ptr.h"
namespace mystl {

template <typename Base> struct poly_view_list {
  template <typename Derived>
    requires std::is_base_of_v<Base, Derived>
  void push_back(observer_ptr<Derived> ptr) {
    container.push_back(static_cast<observer_ptr<Base>>(ptr));
  }

  void push_back(observer_ptr<Base> ptr) { container.push_back(ptr); }

  template <typename Derived>
    requires std::is_base_of_v<Base, Derived>
  void push_front(observer_ptr<Derived> ptr) {
    container.push_front(static_cast<observer_ptr<Base>>(ptr));
  }

  template <bool isConst> struct iterator_impl {
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = observer_ptr<Base>;
    using difference_type = std::ptrdiff_t;
    using pointer =
        std::conditional_t<isConst, const observer_ptr<Base>,
                           observer_ptr<Base>>;
    using reference =
        std::conditional_t<isConst, const Base &, Base &>;

    using container_iterator = typename std::conditional_t<
        isConst,
        typename std::list<observer_ptr<Base>>::const_iterator,
        typename std::list<observer_ptr<Base>>::iterator>;
    explicit iterator_impl(container_iterator it) : it_(it) {}

    pointer operator*() const { return pointer(it_->get()); }

    pointer operator->() const { return pointer(it_->get()); }

    iterator_impl &operator++() {
      ++it_;
      return *this;
    }

    iterator_impl operator++(int) {
      iterator_impl temp = *this;
      ++(*this);
      return temp;
    }

    iterator_impl &operator--() {
      --it_;
      return *this;
    }

    iterator_impl operator--(int) {
      iterator_impl temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const iterator_impl &other) const {
      return it_ == other.it_;
    }

    bool operator!=(const iterator_impl &other) const {
      return !(*this == other);
    }

  private:
    friend poly_view_list;
    container_iterator it_;
  };
  using iterator = iterator_impl<false>;
  using const_iterator = iterator_impl<true>;

  iterator begin() { return iterator(container.begin()); }

  iterator end() { return iterator(container.end()); }

  const_iterator begin() const { return const_iterator(container.cbegin()); }
  const_iterator end() const { return const_iterator(container.cend()); }

  iterator erase(iterator it) { return iterator(container.erase(it.it_)); }

  [[nodiscard]] bool empty() const { return container.empty(); }

  [[nodiscard]] size_t size() const { return container.size(); }

  void clear() { container.clear(); }

private:
  std::list<observer_ptr<Base>> container{};
};
}
#endif //POLY_VIEW_LIST_H
