#include "../list/s21_list.h"
namespace s21 {
template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using Con = s21::list<T>;

 private:
  Con Lcont_;

 public:
  stack() : Lcont_(){};
  stack(std::initializer_list<value_type> const &items) : Lcont_(items){};
  stack(stack const &s) : Lcont_(s.Lcont_){};
  stack(stack &&s) : Lcont_(std::move(s.Lcont_)){};
  ~stack() = default;
  stack &operator=(stack &&s) {
    Lcont_ = std::move(s.Lcont_);
    return *this;
  }
  stack &operator=(const stack &s) {
    Lcont_ = s.Lcont_;
    return *this;
  }
  bool empty() const { return Lcont_.empty(); }
  size_type size() const { return Lcont_.size(); }
  const_reference top() const { return Lcont_.back(); }
  void pop() { Lcont_.pop_back(); }
  void push(const_reference value) { Lcont_.push_back(value); }
  void swap(stack &other) { Lcont_.swap(other.Lcont_); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    for (auto &val : {args...}) {
      Lcont_.push_back(val);
    }
  }
};
}  // namespace s21