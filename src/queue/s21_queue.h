#include "../list/s21_list.h"
namespace s21 {
template <class T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Con = s21::list<T>;

 private:
  Con Lcont_;

 public:
  queue() : Lcont_(){};
  queue(std::initializer_list<value_type> const &items) : Lcont_(items){};
  queue(const queue &q) : Lcont_(q.Lcont_){};
  queue(queue &&q) : Lcont_(std::move(q.Lcont_)){};
  ~queue() = default;
  queue &operator=(queue &&q) {
    Lcont_ = std::move(q.Lcont_);
    return *this;
  }
  queue &operator=(const queue &q) {
    Lcont_ = q.Lcont_;
    return *this;
  }
  const_reference front() const { return Lcont_.front(); }
  const_reference back() const { return Lcont_.back(); }
  bool empty() const { return Lcont_.empty(); }
  size_type size() const { return Lcont_.size(); }
  void push(const_reference value) { Lcont_.push_back(value); }
  void pop() { Lcont_.pop_front(); }
  void swap(queue &other) { Lcont_.swap(other.Lcont_); }
  template <class... Args>
  void insert_many_back(Args &&...args) {
    for (auto &val : {args...}) {
      Lcont_.push_back(val);
    }
  }
};
}  // namespace s21
