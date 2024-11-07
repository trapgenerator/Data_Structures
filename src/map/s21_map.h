#include <initializer_list>

#include "../binary_tree/binary_tree.h"
namespace s21 {
template <class Key, class T>
class map {
 public:
  using key_type = Key;
  using value_type = std::pair<Key, T>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  struct mapCompare {
    int operator()(const_reference a, const_reference b) {
      if (a.first < b.first) return -1;
      if (a.first > b.first) return 1;
      return 0;
    }
    int operator()(Key a, const_reference b) {
      if (a < b.first) return -1;
      if (a > b.first) return 1;
      return 0;
    }
  };
  using iterator =
      typename s21::bintree<key_type, value_type, mapCompare>::iterator;
  using const_iterator =
      typename s21::bintree<key_type, value_type, mapCompare>::const_iterator;

  map() : tree_(){};
  map(const map &m) : tree_(m.tree_){};
  map(map &&m) : tree_(std::move(m.tree_)){};
  map(std::initializer_list<value_type> const &items) : tree_() {
    for (auto it : items) insert(it);
  }
  map &operator=(map &&m) {
    tree_ = std::move(m.tree_);
    return *this;
  }
  map &operator=(const map &m) {
    tree_ = m.tree_;
    return *this;
  }
  ~map() = default;

  T &at(const Key &key) { return (*tree_.at(key)).second; }
  T &operator[](const Key &key) { return at(key); }

  iterator begin() { return tree_.begin(); }
  iterator end() { return tree_.end(); }

  bool empty() const { return tree_.empty(); }
  size_type size() const { return tree_.size(); }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(Key) / 20;
  }

  void clear() { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return tree_.insert(value);
  }
  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return tree_.insert(value_type(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    auto para = tree_.insert(std::make_pair(key, obj));
    if (para.second == false) {
      (*para.first).second = obj;
    }
    para.second = true;
    return para;
  }
  void erase(iterator pos) { tree_.erase(pos); }
  void swap(map &other) { tree_.swap(other.tree_); }

  bool contains(const Key &key) { return tree_.contains(key); }

  void merge(map &other) {
    auto it = other.begin();
    size_type sz = other.size();
    for (size_type i = 0; i < sz; i++) {
      if (!contains(it.pos_->key_.first)) {
        insert(*it);
        it++;
      } else {
        it++;
      }
    }
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    return tree_.insert_many(args...);
  }

 private:
  s21::bintree<key_type, value_type, mapCompare> tree_;
};
}  // namespace s21
