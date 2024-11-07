#ifndef SRC_LIST_LIST_H
#define SRC_LIST_LIST_H
#include <initializer_list>
#include <iostream>
#include <limits>
namespace s21 {
template <class T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

 private:
  int size_;
  class node {
   public:
    T data_;
    node *next_;
    node *prev_;
    node(T data = T(), node *prev = nullptr, node *next = nullptr) {
      data_ = data;
      prev_ = prev;
      next_ = next;
    }
  };
  node *head_;
  node *tail_;
  node *for_it_;

 public:
  list();
  list(size_type n);
  list(const list &l);
  list(list &&l);
  list(std::initializer_list<value_type> const &items);
  ~list();
  list &operator=(list &&other);
  list &operator=(const list &other);
  bool empty() const;
  void pop_front();
  void clear();
  int size() const;
  void push_back(const_reference data);
  void push_front(const_reference data);
  void pop_back();
  const_iterator cbegin() const {
    ListConstIterator beg(head_, *this);
    return beg;
  }
  iterator begin() {
    ListIterator beg(head_, *this);
    return beg;
  }
  const_iterator cend() const {
    ListConstIterator endd(for_it_, *this);
    return endd;
  }
  iterator end() {
    ListIterator endd(for_it_, *this);
    return endd;
  }
  iterator insert(iterator pos, const_reference value);
  const_reference front() const;
  const_reference back() const;
  void merge(list &other);
  void erase(iterator pos);
  void swap(list &other);
  void unique();
  void reverse();
  void sort();
  void splice(const_iterator pos, list &other);
  size_type max_size() const;
  class ListIterator {
   public:
    node *cur_;
    node *beg_;
    node *end_;
    node *for_it_;
    value_type ret = value_type();
    ListIterator(node *cur, const list &pattern);
    ListIterator();
    value_type &operator*();
    iterator &operator++();
    iterator &operator--();
    iterator operator++(int value);
    iterator operator--(int value);
    bool operator==(const iterator other);
    bool operator!=(const iterator other);
    // iterator& operator=(const iterator other) = default;
  };
  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator() : ListIterator() {}
    ListConstIterator(node *cur, const list &pattern)
        : ListIterator(cur, pattern) {}
    const value_type &operator*() { return ListIterator::cur_->data_; }
  };
  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);
};
}  // namespace s21
#include "s21_list.tpp"
#endif