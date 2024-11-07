#include <gtest/gtest.h>

#include <ostream>

#include "../s21_containers.h"

TEST(Set, empty_set_00) {
  s21::set<int> s;
  ASSERT_EQ(s.empty(), true);
  ASSERT_EQ(s.size(), 0);
}
TEST(set_capacity, size_00) {
  s21::set<double> ms;
  std::set<double> sms;
  ASSERT_EQ(ms.max_size(), sms.max_size());
}

TEST(Set, size_01) {
  s21::set<int> s1({{1}, {2}});
  ASSERT_EQ(s1.size(), 2);
}

// TEST(Set, Iterators_00) {
//   s21::set<int> s1({1, 3, 5, 6, 7, 99});
//   std::set<int> s2({1, 3, 5, 6, 7, 99});
//
//   s21::set<int>::iterator init = s1.begin();
//   s21::set<int>::iterator end = s1.end();
//
//   std::set<int>::iterator init_ = s2.begin();
//
//   for (; init != end; ++init, ++init_) {
//     ASSERT_EQ(*init, *init_);
//   }
// }

TEST(Set, remove_00) {
  s21::set<int> s1({1, 3, 5, 6, 7, 99});
  s21::set<int>::iterator it = s1.begin();
  s1.erase(++it);
  it = s1.begin();
  ASSERT_EQ((*++it), 5);
}

TEST(Set, remove_01) {
  s21::set<int> s1{1, 8, 3, 5, 6, 11, 13, 14, 2, 4};
  s21::set<int>::iterator it = s1.find(8);
  s1.erase(it);
  EXPECT_EQ(s1.contains(8), false);
  EXPECT_EQ(s1.size(), 9);
  it = s1.find(5);
  s1.erase(it);
  EXPECT_EQ(s1.contains(5), false);
  EXPECT_EQ(s1.size(), 8);
}

TEST(Set, clean_00) {
  s21::set<int> s1({1, 3, 5, 6, 7, 99});
  s1.clear();
  ASSERT_EQ(s1.empty(), true);
}

TEST(set_mod, merge_00) {
  s21::set<int> s1({3, 5, 6, 7});
  s21::set<int> s2({3, 21, 15});
  s1.merge(s2);
  s21::set<int>::iterator it = s1.begin();
  ASSERT_EQ((*it), 3);
}

TEST(Set, swap_00) {
  s21::set<int> s1({21, 42, 33, 51});
  s21::set<int> s2({999, 45});
  s1.swap(s2);
  s21::set<int>::iterator it = s1.begin();
  ASSERT_EQ((*it), 45);
}

TEST(Set, move_00) {
  s21::set<std::string> s1{"one", "two", "three"};
  s21::set<std::string> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.contains("one"), true);
  s21::set<std::string> s3{"1", "2"};
  s3 = std::move(s1);
  EXPECT_EQ(s3.size(), 0);
  EXPECT_EQ(s3.contains("2"), false);
}

TEST(Set, copy_00) {
  s21::set<int> s1{1, 1, 2, 3, 5, 8};
  s21::set<int> s2 = s1;
  s2 = s2;
  EXPECT_EQ(s2.contains(5), true);
}

TEST(Set, find_00) {
  s21::set<int> s1{1, 1, 2, 3, 5, 8};
  auto it = s1.find(3);
  EXPECT_EQ(*it, 3);
}

TEST(set_iter, Iterators_01) {
  s21::set<int> s1({1, 3, 5, 6, 7, 99});
  s21::set<int>::const_iterator it = s1.cbegin();
  s21::set<int>::const_iterator it_ = s1.cbegin();
  EXPECT_EQ((it == it_), true);
  EXPECT_EQ(*(++it), 3);
  EXPECT_EQ(*(++it), 5);
  EXPECT_EQ(*(--it), 3);
  EXPECT_EQ((it != it_), true);
}

TEST(Set, insert_02) {
  s21::set<int> s1{1, 8, 3};
  s1.insert_many(5, 6, 99);
  EXPECT_EQ(s1.contains(5), true);
  EXPECT_EQ(s1.contains(6), true);
  EXPECT_EQ(s1.contains(99), true);
}

TEST(set, minuses) {
  s21::set<int> s1({1, 3, 5, 6, 7, 99});
  std::set<int> s2({1, 3, 5, 6, 7, 99});

  auto it1 = s1.begin();
  auto it2 = s2.begin();
  it1--;
  it2--;
  it1--;
  it2--;
  it1--;
  it2--;
  ASSERT_EQ(*it1, *it2);
}

TEST(set, minuses1) {
  s21::set<int> s1({1, 3, 5, 6, 7, 99});
  std::set<int> s2({1, 3, 5, 6, 7, 99});
  auto it1 = s1.end();
  auto it2 = s2.end();
  it1--;
  it2--;
  it1--;
  it2--;
  it1--;
  it2--;
  it1--;
  it2--;
  it1--;
  it2--;
  it1--;
  it2--;
  it1--;
  it2--;
  it1--;
  it2--;
  it1--;
  it2--;
  ASSERT_EQ(*it1, *it2);
}

TEST(erase, bounds) {
  s21::set<int> my_set = {5, 4, 3, 2, 7, 8, 9};
  std::set<int> orig_set = {5, 4, 3, 2, 7, 8, 9};
  auto size = my_set.size();
  my_set.erase(my_set.end());
  auto new_size = my_set.size();
  EXPECT_EQ(size, new_size);
  my_set.erase(my_set.begin());
  orig_set.erase(orig_set.begin());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}