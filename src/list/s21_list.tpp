#include "s21_list.h"
namespace s21 {
template <class value_type>
list<value_type>::list() {
  size_ = 0;
  head_ = nullptr;
  tail_ = nullptr;
  for_it_ = new node;
}
template <class value_type>
list<value_type>::list(size_type n) {
  size_ = 0;
  head_ = nullptr;
  tail_ = nullptr;
  for_it_ = new node;
  for (size_type i = 0; i < n; i++) {
    push_back(size_type());
  }
}
template <class value_type>
list<value_type>::list(const list &l) : list() {
  node *current = l.head_;
  while (current != nullptr) {
    push_back(current->data_);
    current = current->next_;
  }
}
template <class value_type>
list<value_type>::list(list &&l) : list() {
  swap(l);
}

template <class value_type>
list<value_type>::list(std::initializer_list<value_type> const &items)
    : list() {
  for (auto it = items.begin(); it != items.end(); it++) {
    push_back(*it);
  }
}
template <class value_type>
list<value_type>::~list() {
  clear();
  tail_ = nullptr;
  delete for_it_;
}
template <class value_type>
list<value_type> &list<value_type>::operator=(list &&other) {
  clear();
  delete for_it_;
  head_ = other.head_;
  tail_ = other.tail_;
  size_ = other.size_;
  for_it_ = other.for_it_;
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
  other.for_it_ = nullptr;
  return *this;
}
template <class value_type>
list<value_type> &list<value_type>::operator=(const list &other) {
  clear();
  node *current = other.head_;
  while (current != nullptr) {
    push_back(current->data_);
    current = current->next_;
  }
  return *this;
}
template <class value_type>
list<value_type>::ListIterator::ListIterator(node *cur, const list &pattern) {
  cur_ = cur;
  beg_ = pattern.head_;
  end_ = pattern.tail_;
  this->for_it_ = pattern.for_it_;
}
template <class value_type>
list<value_type>::ListIterator::ListIterator() {
  cur_ = nullptr;
  beg_ = nullptr;
  end_ = nullptr;
  this->for_it_ = nullptr;
}
template <class value_type>
bool list<value_type>::ListIterator::operator==(const iterator other) {
  bool rez = false;
  if (this->cur_ == other.cur_) rez = true;
  return rez;
}
template <class value_type>
bool list<value_type>::ListIterator::operator!=(const iterator other) {
  bool rez = false;
  if (this->cur_ != other.cur_) rez = true;
  return rez;
}
template <class value_type>
typename list<value_type>::value_type &
list<value_type>::ListIterator::operator*() {
  if (cur_ != nullptr) return cur_->data_;
  return ret;
}
template <class value_type>
typename list<value_type>::iterator &
list<value_type>::ListIterator::operator++() {
  if (cur_ != nullptr && cur_ != for_it_) {
    if (cur_->next_ == nullptr) {
      cur_ = for_it_;
    } else
      cur_ = cur_->next_;
  } else {
    cur_ = beg_;
  }
  return *this;
}
template <class value_type>
typename list<value_type>::iterator list<value_type>::ListIterator::operator++(
    int) {
  if (cur_ != nullptr && cur_ != for_it_) {
    if (cur_->next_ == nullptr) {
      cur_ = for_it_;
    } else
      cur_ = cur_->next_;
  } else {
    cur_ = beg_;
  }
  return *this;
}
template <class value_type>
typename list<value_type>::iterator &
list<value_type>::ListIterator::operator--() {
  if (cur_ != nullptr && cur_ != for_it_) {
    if (cur_->prev_ == nullptr) {
      cur_ = for_it_;
    } else
      cur_ = cur_->prev_;
  } else {
    cur_ = end_;
  }
  return *this;
}
template <class value_type>
typename list<value_type>::iterator list<value_type>::ListIterator::operator--(
    int value) {
  if (cur_ != nullptr && cur_ != for_it_) {
    if (cur_->prev_ == nullptr) {
      cur_ = for_it_;
    } else
      cur_ = cur_->prev_;
  } else {
    cur_ = end_;
  }
  return *this;
}
template <class value_type>
bool list<value_type>::empty() const {
  bool rez;
  if (head_ == nullptr)
    rez = true;
  else
    rez = false;
  return rez;
};
template <class value_type>
typename list<value_type>::iterator list<value_type>::insert(
    iterator pos, const_reference value) {
  iterator new_it = pos;
  if (pos.cur_ == nullptr) {
    push_back(value);
    new_it = begin();
  } else if (pos.cur_ == head_) {
    push_front(value);
    --new_it;
  } else if (pos.cur_ != for_it_) {
    node *new_element = new node(value, pos.cur_->prev_, pos.cur_);
    new_element->prev_->next_ = new_element;
    new_element->next_->prev_ = new_element;
    size_++;
    --new_it;
  } else {
    push_back(value);
    new_it = --end();
  }
  return new_it;
}
template <class value_type>
typename list<value_type>::const_reference list<value_type>::front() const {
  return *cbegin();
}
template <class value_type>
typename list<value_type>::const_reference list<value_type>::back() const {
  return *(--cend());
}
template <class value_type>
void list<value_type>::merge(list &other) {
  tail_->next_ = other.head_;
  this->size_ += other.size_;
  other.size_ = 0;
  tail_ = other.tail_;
  other.head_ = nullptr;
  other.tail_ = nullptr;
}
template <class value_type>
void list<value_type>::erase(iterator pos) {
  if (!empty()) {
    if (pos.cur_ != head_) {
      pos.cur_->prev_->next_ = pos.cur_->next_;
      pos.cur_->next_->prev_ = pos.cur_->prev_;
      pos.ret = pos.cur_->data_;
      delete pos.cur_;
      pos.cur_ = nullptr;
      size_--;
    } else {
      pos.cur_->next_->prev_ = nullptr;
      head_ = pos.cur_->next_;
      delete pos.cur_;
      pos.cur_ = nullptr;
      size_--;
    }
  }
}

template <class value_type>
void list<value_type>::unique() {
  node *current = head_;
  if (current != nullptr) {
    while (current->next_ != nullptr) {
      if (current->data_ == current->next_->data_) {
        if (current->next_->next_ != nullptr) {
          current->next_->next_->prev_ = current;
          node *cur = current->next_->next_;
          delete current->next_;
          current->next_ = cur;
        } else {
          delete current->next_;
          current->next_ = nullptr;
        }
        size_--;
      } else {
        current = current->next_;
      }
    }
  }
}

template <class value_type>
void list<value_type>::reverse() {
  node *current = head_;
  while (current != nullptr) {
    node *cur = current->prev_;
    current->prev_ = current->next_;
    current->next_ = cur;
    current = current->prev_;
  }
  node *cur2 = head_;
  head_ = tail_;
  tail_ = cur2;
}

template <class value_type>
void list<value_type>::sort() {
  if (empty()) {
    return;
  }
  int cp_size = size_;
  for (int i = 0; i < cp_size; i++) {
    node *current = head_;
    while (current->next_ != nullptr) {
      if (current->data_ > current->next_->data_) {
        value_type datanew = current->data_;
        current->data_ = current->next_->data_;
        current->next_->data_ = datanew;
      }
      current = current->next_;
    }
    cp_size--;
  }
}

template <class value_type>
void list<value_type>::splice(const_iterator pos, list &other) {
  node *curh = other.head_;
  node *curt = other.tail_;
  if (pos.cur_ != nullptr) {
    if (pos.cur_->prev_ != nullptr && pos.cur_ != for_it_) {
      pos.cur_->prev_->next_ = curh;
      curt->prev_ = pos.cur_->prev_;
      curt->next_ = pos.cur_;
      pos.cur_->prev_ = curt;
    } else if (pos.cur_ == for_it_) {
      tail_->next_ = curh;
      curh->prev_ = tail_;
      tail_ = curt;
    } else {
      pos.cur_->prev_ = curt;
      curt->next_ = pos.cur_;
      head_ = curh;
      tail_ = pos.cur_;
    }
  } else {
    head_ = other.head_;
    tail_ = other.tail_;
  }
  size_ += other.size_;
  other.tail_ = nullptr;
  other.head_ = nullptr;
  other.size_ = 0;
}
template <class value_type>
void list<value_type>::swap(list &other) {
  if (this != &other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
    std::swap(for_it_, other.for_it_);
  }
}

template <class value_type>
int list<value_type>::size() const {
  return size_;
};
template <class value_type>
void list<value_type>::push_back(const_reference data) {
  if (head_ == nullptr) {
    head_ = new node(data);
    tail_ = head_;
    size_++;
  } else {
    node *current = tail_;
    tail_->next_ = new node(data);
    tail_ = tail_->next_;
    tail_->prev_ = current;
    size_++;
  }
}
template <class value_type>
void list<value_type>::push_front(const_reference data) {
  if (head_ == nullptr) {
    head_ = new node(data);
    tail_ = head_;
    size_++;
  } else {
    node *current = head_;
    head_->prev_ = new node(data);
    head_ = head_->prev_;
    head_->next_ = current;
    size_++;
  }
}
template <class value_type>
void list<value_type>::pop_front() {
  if (size_ != 0) {
    node *current = head_;
    head_ = head_->next_;
    delete current;
    if (current == tail_) {
      tail_ = nullptr;
    }
    current = nullptr;
    size_--;
  }
}
template <class value_type>
void list<value_type>::clear() {
  while (size_ != 0) {
    pop_front();
  }
}
template <class value_type>
void list<value_type>::pop_back() {
  if (size_ != 0) {
    node *current = tail_;
    tail_ = tail_->prev_;
    delete current;
    if (current == head_) {
      head_ = nullptr;
    }
    current = nullptr;
    size_--;
  }
}
template <class value_type>
typename list<value_type>::size_type list<value_type>::max_size() const {
  return (std::numeric_limits<size_type>::max() / sizeof(node)) / 2;
}
template <class value_type>
template <class... Args>
typename list<value_type>::iterator list<value_type>::insert_many(
    const_iterator pos, Args &&...args) {
  for (auto &val : {args...}) {
    insert(pos, val);
  }
  return pos;
}
template <class value_type>
template <class... Args>
void list<value_type>::insert_many_back(Args &&...args) {
  for (auto &val : {args...}) {
    push_back(val);
  }
}
template <class value_type>
template <class... Args>
void list<value_type>::insert_many_front(Args &&...args) {
  auto pos = begin();
  for (auto &val : {args...}) {
    insert(pos, val);
  }
}
}  // namespace s21
