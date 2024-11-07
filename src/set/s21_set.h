#include <initializer_list>

#include "../binary_tree/binary_tree.h"
namespace s21 {
template <class Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  struct setCompare {
    int operator()(const key_type a, const key_type b) {
      if (a < b) return -1;
      if (a > b) return 1;
      return 0;
    }
  };
  using iterator = typename s21::bintree<Key, Key, setCompare>::iterator;
  using const_iterator =
      typename s21::bintree<Key, Key, setCompare>::const_iterator;
  set() : tree_(){};
  set(const set &s) : tree_(s.tree_){};
  set(set &&s) : tree_(std::move(s.tree_)){};
  set(std::initializer_list<value_type> const &items) : tree_() {
    for (auto it = items.begin(); it != items.end(); it++) tree_.insert(*it);
  }
  ~set() = default;
  set &operator=(const set &other) {
    tree_ = other.tree_;
    return *this;
  }
  set &operator=(set &&other) {
    tree_ = std::move(other.tree_);
    return *this;
  }
  size_type size() const { return tree_.size(); }
  bool empty() { return tree_.empty(); }
  iterator begin() { return tree_.begin(); }
  iterator end() { return tree_.end(); }
  iterator find(const Key &key) { return tree_.find(key); }
  bool contains(const Key &key) { return tree_.contains(key); }
  void erase(iterator pos) { return tree_.erase(pos); }
  void swap(set &other) { tree_.swap(other.tree_); }
  std::pair<iterator, bool> insert(const value_type &value) {
    return tree_.insert(value);
  }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(Key) / 10;
  }
  void merge(set &other) { return tree_.merge(other.tree_); }
  void clear() { tree_.clear(); }
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return tree_.insert_many(args...);
  }
  const_iterator cbegin() { return tree_.cbegin(); }

  const_iterator cend() { return tree_.cbegin(); }

 private:
  s21::bintree<key_type, key_type, setCompare> tree_;
};
};  // namespace s21
