
namespace s21 {
// constructors and destructor
template <typename T>
vector<T>::vector() {
  size_ = 0;
  capacity_ = 0;
  arr_ = nullptr;
}
template <typename T>
vector<T>::vector(size_type n)
    : size_(n), capacity_(n), arr_(new value_type[capacity_]) {}
template <typename T>
vector<T>::vector(const vector &v) : size_(v.size_), capacity_(v.capacity_) {
  arr_ = new T[capacity_];
  for (size_type i = 0; i < v.size_; i++) {
    arr_[i] = v.arr_[i];
  }
}
template <typename T>
vector<T>::vector(vector &&v) {
  size_ = v.size_;
  capacity_ = v.capacity_;
  arr_ = v.arr_;
  v.size_ = 0;
  v.capacity_ = 0;
  v.arr_ = nullptr;
}
template <typename T>
vector<T>::~vector() {
  if (arr_) {
    delete[] this->arr_;
  }
  arr_ = nullptr;
  capacity_ = 0;
  size_ = 0;
}

template <typename T>
vector<T>::vector(std::initializer_list<T> const &items) {
  this->capacity_ = this->size_ = items.size();
  if (this->size_) {
    this->arr_ = new T[this->size_];
    std::copy(items.begin(), items.end(), this->arr_);
  }
};

// methods
template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    capacity_ *= 2;
    value_type *buff = new value_type[capacity_];
    for (size_type i = 0; i < this->size_; ++i) {
      buff[i] = this->arr_[i];
    }
    delete[] this->arr_;
    arr_ = buff;
  }
  arr_[size_++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    size_--;
    // TODO: think about clear realization
  }
}

// funcs
template <typename T>
void vector<T>::reserve(size_type new_cap) {
  if (this->size_ >= this->capacity_ && new_cap > this->capacity_) {
    value_type *buff = new value_type[new_cap];
    for (size_type i = 0; i < this->size_; ++i) {
      buff[i] = this->arr_[i];
    }
    delete[] this->arr_;
    arr_ = buff;
    capacity_ = new_cap;
  }
}

// operators
template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos > size_) {
    std::logic_error("Out of range");
  }
  return this->arr_[pos];
}

template <typename T>
typename s21::vector<T> &vector<T>::operator=(vector &&v) {
  if (this != &v) {
    if (this->arr_) {
      delete[] this->arr_;
    }
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->arr_ = v.arr_;
    v.size_ = 0;
    v.capacity_ = 0;
    v.arr_ = nullptr;
  }
  return *this;
}

template <typename T>
typename s21::vector<T> &vector<T>::operator=(const vector &v) {
  if (this != &v && v.arr_ != nullptr) {
    if (this->arr_ != nullptr) {
      delete[] this->arr_;
    }
    this->arr_ = nullptr;
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->arr_ = new T[this->capacity_];
    for (size_type i = 0; i < v.size_; i++) {
      this->arr_[i] = v.arr_[i];
    }
  }
  return *this;
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  // if(size_ < 0){
  //     std::logic_error("Out of range");
  // }
  return *this->arr_;
}
template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  // if(size_ < 0){
  //     //std::logic_error("Out of range");
  // }
  return this->arr_[size_ - 1];
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return this->size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return this->capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ != capacity_ && this->arr_ != nullptr) {
    T *temp = new T[this->size_];
    for (size_type i = 0; i < this->size_; i++) {
      temp[i] = this->arr_[i];
    }
    delete[] this->arr_;
    this->arr_ = nullptr;
    this->arr_ = temp;
    capacity_ = size_;
  }
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= this->size_) {
    std::logic_error("Out of range");
  }
  return this->arr_[pos];
}

template <typename T>
typename vector<T>::pointer vector<T>::data() {
  return this->arr_;
}

template <typename T>
bool vector<T>::empty() {
  return size_ == 0;
}

template <typename T>
void vector<T>::clear() {
  this->size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(arr_);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(arr_ + size_);
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type k = &(*pos) - this->arr_;
  if (size_ >= capacity_) {
    reserve(size_ * 2);
  }
  size_type zerr = 0;
  if (k < zerr || k > size_) {
    std::logic_error("Out of range");
  }
  T save = this->arr_[k];
  this->arr_[k] = value;
  size_++;
  for (size_type i = k + 1; i < this->size(); i++) {
    T replace = this->arr_[i];
    arr_[i] = save;
    save = replace;
  }
  return arr_ + k;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type k = &(*pos) - this->arr_;
  size_type zerr = 0;
  if (k < zerr || k > size_) {
    std::logic_error("Out of range");
  } else {
    for (size_type i = k + 1; i < this->size(); i++) {
      this->arr_[i - 1] = this->arr_[i];
    }
  }
  size_--;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(other.size_, this->size_);
  std::swap(other.capacity_, this->capacity_);
  std::swap(other.arr_, this->arr_);
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
#ifdef __linux__
  return std::numeric_limits<size_type>::max() / (sizeof(T) * 2);
#else
  std::numeric_limits<size_type>::max() / sizeof(T);
#endif
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  iterator ps = pos;
  int count = 0;
  for (const auto &val : {std::forward<Args>(args)...}) {
    this->insert(ps, val);
    count++;
    ps = this->begin();
    for (int i = 0; i < count; i++) {
      ps++;
    }
  }
  return ps;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  for (const auto &val : {std::forward<Args>(args)...}) {
    this->push_back(val);
  }
}

}  // namespace s21