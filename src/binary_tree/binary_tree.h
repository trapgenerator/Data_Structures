#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>
#include <limits>
#include <vector>
namespace s21 {
template <class Key, class value_type, class compare>
class bintree {
 public:
  class TreeIterator;
  class Const_Tree_Iterator;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using key_type = Key;
  using iterator = TreeIterator;
  using const_iterator = Const_Tree_Iterator;

 private:
  class node {
   public:
    value_type key_;
    node *right_;
    node *left_;
    node *parent_;
    node(const_reference key = value_type(), node *parent = nullptr,
         node *right = nullptr, node *left = nullptr) {
      key_ = key;
      right_ = right;
      left_ = left;
      parent_ = parent;
    }
  };
  size_type size_;
  node *root_;
  node *it_end_;
  compare compare_;

 public:
  bintree() {
    root_ = nullptr;
    size_ = 0;
    it_end_ = new node;
  }
  bintree(const bintree &other) : bintree() {
    root_ = cp_node(other.root_);
    size_ = other.size_;
  }
  bintree(bintree &&other) {
    root_ = other.root_;
    it_end_ = other.it_end_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.it_end_ = nullptr;
    other.size_ = 0;
  }
  ~bintree() {
    clear();
    delete it_end_;
  }
  bintree &operator=(const bintree &other) {
    if (&other != this) {
      clear();
      root_ = cp_node(other.root_);
      size_ = other.size_;
    }
    return *this;
  }
  bintree &operator=(bintree &&other) {
    clear();
    delete it_end_;
    root_ = other.root_;
    it_end_ = other.it_end_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.it_end_ = nullptr;
    other.size_ = 0;
    return *this;
  }
  node *cp_node(const node *other) {
    node *current = nullptr;
    if (other != nullptr) {
      current = new node(other->key_);
      current->left_ = cp_node(other->left_);
      current->right_ = cp_node(other->right_);
    }
    return current;
  }
  void clear() {
    del(root_);
    root_ = nullptr;
  }
  void del(node *root) {
    if (root != nullptr) {
      del(root->left_);
      del(root->right_);
      delete root;
      root = nullptr;
    }
  }
  std::pair<iterator, bool> insert(const_reference key) {
    std::pair<iterator, bool> para;
    if (root_ == nullptr) {
      root_ = new node(key);
      ++size_;
      para.first = begin();
      para.second = true;
    } else {
      node *current = root_;
      node *desc = nullptr;
      while (current != nullptr) {
        desc = current;
        if (compare_(key, current->key_) == 1) {
          if (current->right_ != nullptr)
            current = current->right_;
          else {
            current->right_ = new node(key, desc);
            ++size_;
            iterator it(current->right_, it_end_, root_);
            para.first = it;
            para.second = true;
            current = nullptr;
          }
        } else if (compare_(key, current->key_) == 0) {
          iterator it(current, it_end_, root_);
          para.first = it;
          para.second = false;
          break;
        } else {
          if (current->left_ != nullptr)
            current = current->left_;
          else {
            current->left_ = new node(key, desc);
            ++size_;
            iterator it(current->left_, it_end_, root_);
            para.first = it;
            para.second = true;
            current = nullptr;
          }
        }
      }
    }
    return para;
  }
  size_type size() const { return size_; }
  bool empty() const {
    if (root_ == nullptr)
      return true;
    else
      return false;
  }
  void erase(iterator pos) {
    if (pos == end() || pos.pos_ == nullptr) return;
    if (pos.pos_->left_ == nullptr && pos.pos_->right_ == nullptr) {
      if (pos.pos_->parent_ != nullptr) {
        if (compare_(pos.pos_->parent_->key_, pos.pos_->key_) == 1) {
          pos.pos_->parent_->left_ = nullptr;
        } else {
          pos.pos_->parent_->right_ = nullptr;
        }
      }
      delete pos.pos_;
      pos.pos_ = nullptr;
    } else if (pos.pos_->left_ == nullptr && pos.pos_->right_ != nullptr) {
      if (pos.pos_->parent_ != nullptr) {
        if (compare_(pos.pos_->parent_->key_, pos.pos_->key_) == 1) {
          pos.pos_->parent_->left_ = pos.pos_->right_;
        } else {
          pos.pos_->parent_->right_ = pos.pos_->right_;
        }
      } else
        root_ = pos.pos_;
      pos.pos_->right_->parent_ = pos.pos_->parent_;
      delete pos.pos_;
      pos.pos_ = nullptr;
    } else if (pos.pos_->left_ != nullptr && pos.pos_->right_ == nullptr) {
      if (pos.pos_->parent_ != nullptr) {
        if (compare_(pos.pos_->parent_->key_, pos.pos_->key_) == 1) {
          pos.pos_->parent_->left_ = pos.pos_->left_;
        } else {
          pos.pos_->parent_->right_ = pos.pos_->left_;
        }
      } else
        root_ = pos.pos_;

      pos.pos_->left_->parent_ = pos.pos_->parent_;
      delete pos.pos_;
      pos.pos_ = nullptr;
    } else {
      node *current = pos.pos_->right_;
      while (current->left_ != nullptr) {
        current = current->left_;
      }
      if (pos.pos_->right_ != current) {
        current->parent_->left_ = current->right_;
        if (current->right_ != nullptr)
          current->right_->parent_ = current->parent_;
        current->right_ = pos.pos_->right_;
        current->right_->parent_ = current;
      }
      current->parent_ = pos.pos_->parent_;
      current->left_ = pos.pos_->left_;
      current->left_->parent_ = current;
      if (pos.pos_->parent_ != nullptr) {
        if (compare_(pos.pos_->parent_->key_, pos.pos_->key_) == 1) {
          pos.pos_->parent_->left_ = current;
        } else {
          pos.pos_->parent_->right_ = current;
        }
      } else {
        root_ = current;
      }

      delete pos.pos_;
      pos.pos_ = nullptr;
    }
    size_--;
  }
  bool contains(const Key &key) {
    bool rez = false;
    node *current = root_;
    while (current != nullptr) {
      if (compare_(key, current->key_) == 1) {
        current = current->right_;
      } else if (compare_(key, current->key_) == 0) {
        rez = true;
        break;
      } else {
        current = current->left_;
      }
    }
    return rez;
  }

  bool contains_ms(const Key &key) {
    bool rez = false;
    node *current = root_;
    while (current != nullptr) {
      if (compare_(key, current->key_) == 1 && key == current->key_) {
        rez = true;
        break;
      }
      if (compare_(key, current->key_) == 1) {
        current = current->right_;
        if (key == current->key_) {
          rez = true;
          break;
        }
      } else {
        current = current->left_;
      }
    }
    return rez;
  }

  iterator find(const key_type &key) {
    node *current = root_;
    iterator it(nullptr, it_end_, root_);
    while (current != nullptr) {
      if (compare_(key, current->key_) == 1) {
        current = current->right_;
      } else if (compare_(key, current->key_) == 0) {
        it.pos_ = current;
        break;
      } else {
        current = current->left_;
      }
    }
    if (it.pos_ == nullptr) it = end();
    return it;
  }

  iterator find_ms(const key_type &key) {
    node *current = root_;
    iterator it(nullptr, it_end_, root_);
    while (current != nullptr) {
      if (compare_(key, current->key_) == 1) {
        current = current->right_;
        if (key == current->key_) {
          it.pos_ = current;
          break;
        }
      } else {
        current = current->left_;
      }
    }
    if (it.pos_ == nullptr) it = end();
    return it;
  }

  void swap(bintree &other) {
    if (this != &other) {
      std::swap(root_, other.root_);
      std::swap(it_end_, other.it_end_);
      std::swap(size_, other.size_);
    }
  }
  iterator at(const Key &key) { return find(key); }
  void merge(bintree &other) {
    auto it = other.begin();
    size_type sz = other.size_;
    for (size_type i = 0; i < sz; i++) {
      if (!contains(*it)) {
        insert(*it);
        // auto it1 = it;
        it++;
        // erase(it1);
      } else {
        it++;
      }
    }
  }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(node) / 2;
  }
  iterator begin() {
    node *current = root_;
    iterator it(nullptr, it_end_, root_);
    if (current != nullptr) {
      while (current->left_ != nullptr) {
        current = current->left_;
      }
      it.pos_ = current;
    } else {
      it = end();
    }
    return it;
  }
  iterator end() {
    iterator it(it_end_, it_end_, root_);
    return it;
  }
  const_iterator cbegin() {
    const_iterator it(root_, it_end_, root_);
    while (it.pos_ != nullptr && it.pos_->left_ != nullptr) {
      it.pos_ = it.pos_->left_;
    }
    return it;
  }

  const_iterator cend() {
    const_iterator it(nullptr, it_end_, root_);
    return it;
  }

  size_type count(const Key &key) {
    size_type count = 0;
    node *current = root_;
    while (current != nullptr) {
      if (current->key_ == key) {
        count++;
      }
      if (current->key_ > key) {
        current = current->left_;
      } else {
        current = current->right_;
      }
    }
    return count;
  }

  iterator lower_bound(const Key &key) {
    node *x = nullptr;
    node *y = root_;
    while (y != nullptr) {
      if ((y->key_ >= key)) {
        x = y;
        y = y->left_;
      } else {
        y = y->right_;
      }
    }
    iterator it(x, it_end_, root_);
    return it;
  }

  iterator upper_bound(const Key &key) {
    node *x = nullptr;
    node *y = root_;
    while (y != nullptr) {
      if ((y->key_ > key)) {
        x = y;
        y = y->left_;
      } else {
        y = y->right_;
      }
    }
    iterator it(x, it_end_, root_);
    return it;
  }

  class TreeIterator {
   public:
    node *pos_;
    node *end_;
    node *root_;

    value_type ret_ = value_type();
    TreeIterator() {
      pos_ = nullptr;
      end_ = nullptr;
      root_ = nullptr;
    }
    TreeIterator(node *pos, node *end, node *root) {
      pos_ = pos;
      end_ = end;
      root_ = root;
    }
    ~TreeIterator() = default;
    reference operator*() {
      if (pos_ != nullptr) {
        return pos_->key_;
      }
      return ret_;
    }
    bool operator==(const iterator &other) {
      if (pos_ == other.pos_) {
        return true;
      } else {
        return false;
      }
    }
    bool operator!=(const iterator &other) {
      if (pos_ != other.pos_) {
        return true;
      } else {
        return false;
      }
    }
    iterator &operator++() {
      if (pos_ != nullptr) {
        if ((pos_ == nullptr && root_ != nullptr) || pos_ == end_) {
          pos_ = root_->right_;
          while (pos_ != nullptr && pos_->right_ != nullptr) {
            pos_ = pos_->right_;
          }
        } else if (pos_->right_ != nullptr) {
          pos_ = pos_->right_;
          while (pos_->left_ != nullptr) {
            pos_ = pos_->left_;
          }
        } else {
          node *parent = pos_->parent_;
          while (parent != nullptr && pos_ == parent->right_) {
            pos_ = parent;
            parent = parent->parent_;
          }
          pos_ = parent;
          if (pos_ == nullptr) {
            pos_ = end_;
          }
        }
      }
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      operator++();
      return tmp;
    }

    iterator &operator--() {
      if ((pos_ == nullptr && root_ != nullptr) || pos_ == end_) {
        pos_ = root_->right_;
        while (pos_ != nullptr && pos_->right_ != nullptr) {
          pos_ = pos_->right_;
        }
      } else {
        if (pos_->left_ != nullptr) {
          pos_ = pos_->left_;
          while (pos_ != nullptr && pos_->right_ != nullptr) {
            pos_ = pos_->right_;
          }
        } else {
          node *parent = pos_->parent_;
          while (parent != nullptr && pos_ == parent->left_) {
            pos_ = parent;
            parent = parent->parent_;
          }
          pos_ = parent;
        }
      }
      return *this;
    }

    iterator operator--(int) {
      iterator tmp = *this;
      operator--();
      return tmp;
    }
  };

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> rez;
    for (auto &elem : {args...}) {
      rez.push_back(insert(elem));
    }
    return rez;
  }

  class Const_Tree_Iterator : public TreeIterator {
   public:
    Const_Tree_Iterator() : TreeIterator() {}
    Const_Tree_Iterator(node *pos, node *end, node *root)
        : TreeIterator(pos, end, root) {}

    const_reference operator*() { return TreeIterator::pos_->key_; }
  };
};
};  // namespace s21

#endif