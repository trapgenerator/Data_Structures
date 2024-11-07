#include <initializer_list>

#include "../binary_tree/binary_tree.h"

namespace s21 {

template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  struct multisetCompare {
    int operator()(const key_type a, const key_type b) const noexcept {
      if (a < b) {
        return -1;
      } else if (a > b) {
        return 1;
      } else if (a == b) {
        return 1;
      }
      return 0;
    }
  };
  using iterator = typename s21::bintree<Key, Key, multisetCompare>::iterator;
  using const_iterator =
      typename s21::bintree<Key, Key, multisetCompare>::const_iterator;
  // constructors
  multiset() : tree_(){};

  multiset(const multiset &ms) : tree_(ms.tree_){};

  multiset(multiset &&ms) : tree_(std::move(ms.tree_)){};

  multiset(std::initializer_list<value_type> const &items) : tree_() {
    for (auto it = items.begin(); it != items.end(); it++) {
      tree_.insert(*it);
    }
  }

  ~multiset() = default;

  // operators
  multiset &operator=(multiset &&ms) {
    tree_ = std::move(ms.tree_);
    return *this;
  }

  multiset &operator=(const multiset &other) {
    tree_ = other.tree_;
    return *this;
  }

  size_type size() const { return tree_.size(); }

  bool empty() const { return tree_.empty(); }

  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(Key) / 20;
  }

  iterator begin() { return tree_.begin(); }

  iterator end() { return tree_.end(); }

  void clear() { tree_.clear(); }

  void erase(iterator pos) { tree_.erase(pos); }

  std::pair<iterator, bool> insert(const value_type &val) {
    return tree_.insert(val);
  }

  void merge(multiset &other) { return tree_.merge(other.tree_); }

  void swap(multiset &other) { return tree_.swap(other.tree_); }

  iterator find(const key_type &key) { return tree_.find_ms(key); }

  bool contains(const Key &key) { return tree_.contains_ms(key); }

  size_type count(const Key &key) { return tree_.count(key); }

  iterator lower_bound(const Key &key) { return tree_.lower_bound(key); }

  iterator upper_bound(const Key &key) { return tree_.upper_bound(key); }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    return std::make_pair(lower_bound(key), upper_bound(key));
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return tree_.insert_many(args...);
  }

 private:
  s21::bintree<key_type, key_type, multisetCompare> tree_;
};

}  // namespace s21