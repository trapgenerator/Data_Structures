#include <iostream>
#include <limits>
namespace s21 {

template <typename T, std::size_t Size_>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = T *;
  using const_iterator = const iterator;

  array(){};

  array(std::initializer_list<value_type> const &items) {
    std::copy(items.begin(), items.end(), data_);
  }

  array(const array &other) {
    for (size_type i = 0; i < Size_; i++) {
      this->data_[i] = other.data_[i];
    }
  }

  array(array &&other) {
    for (size_type i = 0; i < Size_; i++) {
      data_[i] = std::move(other.data_[i]);
    }
  }

  ~array() = default;

  array &operator=(array &&a) {
    for (size_type i = 0; i < Size_; i++) {
      this->data_[i] = a.data_[i];
    }
    return *this;
  }

  reference operator[](size_type pos) { return data_[pos]; }

  reference at(size_type pos) {
    size_type zerr = 0;
    if (pos >= Size_ || pos < zerr) {
      std::logic_error("Out of range");
    }
    return data_[pos];
  }

  const_reference front() { return data_[0]; }

  const_reference back() { return data_[Size_ - 1]; }

  bool empty() { return Size_ == 0; }

  size_type size() { return Size_; }

  size_type max_size() { return Size_; }

  void swap(array &other) { std::swap(this->data_, other.data_); }

  void fill(const_reference value) {
    for (size_type i = 0; i < Size_; i++) {
      data_[i] = value;
    }
  }

  iterator data() { return data_; }

  iterator begin() { return data_; }

  iterator end() { return data_ + Size_; }

 private:
  value_type data_[Size_];
};

}  // namespace s21
