#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>
namespace s21 {

template <typename T>
class Vector_Iterator;
template <typename T>
class Const_Vector_Iterator;

template <typename T>
class vector {
 public:
  using value_type = T;
  using size_type = size_t;
  using reference = T &;
  using const_reference = const T &;
  using iterator = Vector_Iterator<T>;
  using const_iterator = Const_Vector_Iterator<T>;
  using pointer = T *;

 private:
  size_type size_;
  size_type capacity_;
  T *arr_;

 public:
  // Member functions
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);  // copy constructor
  vector(vector &&v);       // move constructor
  ~vector();
  vector &operator=(vector &&v);
  vector &operator=(const vector &v);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

  // Element access
  reference at(size_type pos);          // done
  reference operator[](size_type pos);  // done
  const_reference front();              // done
  const_reference back();               // done
  T *data();

  // Vector iterators
  iterator begin();
  iterator end();

  // Vector capacity
  bool empty();            // done
  size_type size() const;  // done
  size_type max_size() const;
  void reserve(size_type new_cap);  // done
  size_type capacity() const;       // done
  void shrink_to_fit();             // done

  // Vector modifiers
  void clear();  // done
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);               // done
  void push_back(const_reference value);  // done
  void pop_back();                        // done
  void swap(vector &other);               // done
};

template <typename T>
class Vector_Iterator { /*full done*/
  friend class vector<T>;
  friend class Const_Vector_Iterator<T>;
  using value_type = T;
  using reference = T &;
  using pointer = T *;
  using size_type = size_t;

 public:
  Vector_Iterator() : ptr_(nullptr){};
  Vector_Iterator(pointer ptr) { ptr_ = ptr; }

  value_type &operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }
  Vector_Iterator &operator++() {
    ptr_++;
    return *this;
  }
  Vector_Iterator &operator--() {
    ptr_--;
    return *this;
  }
  Vector_Iterator operator++(int) {
    Vector_Iterator prev = *this;
    ++(*this);
    return prev;
  }

  Vector_Iterator operator--(int) {
    Vector_Iterator prev = *this;
    --(*this);
    return prev;
  }

  Vector_Iterator operator+(const size_type pos) {
    Vector_Iterator tmp(this->ptr_ + pos);
    return tmp;
  }

  Vector_Iterator operator-(const size_type pos) {
    Vector_Iterator tmp(this->ptr_ - pos);
    return tmp;
  }

  bool operator==(const Vector_Iterator &other) {
    return this->ptr_ == other.ptr_;
  }
  bool operator!=(const Vector_Iterator &other) {
    return this->ptr_ != other.ptr_;
  }

  operator Const_Vector_Iterator<T>() const {
    return Const_Vector_Iterator<T>(this->ptr_);
  }

 private:
  pointer ptr_;
};

template <typename T>
class Const_Vector_Iterator { /*full done*/
  friend class vector<T>;
  friend class Vector_Iterator<T>;
  using value_type = T;
  using reference = T &;
  using pointer = T *;
  using size_type = size_t;

 public:
  Const_Vector_Iterator() : ptr_(nullptr){};
  Const_Vector_Iterator(pointer ptr) { ptr_ = ptr; }

  value_type &operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }
  Const_Vector_Iterator &operator++() {
    ptr_++;
    return *this;
  }
  Const_Vector_Iterator &operator--() {
    ptr_--;
    return *this;
  }
  Const_Vector_Iterator operator++(int) {
    Const_Vector_Iterator prev = *this;
    ++(*this);
    return prev;
  }

  Const_Vector_Iterator operator--(int) {
    Const_Vector_Iterator prev = *this;
    --(*this);
    return prev;
  }

  Const_Vector_Iterator operator+(const size_type pos) {
    Const_Vector_Iterator tmp(this->ptr_ + pos);
    return tmp;
  }

  Const_Vector_Iterator operator-(const size_type pos) {
    Const_Vector_Iterator tmp(this->ptr_ - pos);
    return tmp;
  }

  bool operator==(const Const_Vector_Iterator &other) {
    return this->ptr_ == other.ptr_;
  }
  bool operator!=(const Const_Vector_Iterator &other) {
    return this->ptr_ != other.ptr_;
  }

  operator Vector_Iterator<T>() { return Vector_Iterator<T>(this->ptr_); }

 private:
  pointer ptr_;
};

}  // namespace s21
#include "s21_vector.tpp"
