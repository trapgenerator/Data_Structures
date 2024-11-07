#include <gtest/gtest.h>

#include <list>

#include "../list/s21_list.h"
TEST(list, Constructor_Default) {
  s21::list<int> our_list;
  std::list<int> std_list;
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(list, Constructor_Size) {
  s21::list<int> our_list(5);
  std::list<int> std_list(5);
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(list, Constructor_list) {
  s21::list<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(list, Constructor_Copy) {
  s21::list<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::list<int> our_copy(our_list);
  std::list<int> std_copy(std_list);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(list, Operator_Copy) {
  s21::list<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::list<int> our_copy;
  our_copy = our_list;
  std::list<int> std_copy;
  std_copy = std_list;
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(list, Constructor_Move) {
  s21::list<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::list<int> our_copy(std::move(our_list));
  std::list<int> std_copy(std::move(std_list));
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(list, Operator_Move) {
  s21::list<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::list<int> our_copy;
  our_copy = std::move(our_list);
  std::list<int> std_copy;
  std_copy = std::move(std_list);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(list, size) {
  s21::list<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(list, push_front) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.push_front(1);
  std_list.push_front(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(2);
  std_list.push_front(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(3);
  std_list.push_front(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(list, push_back) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(list, Pop_front) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.pop_front();
  std_list.pop_front();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(list, Pop_Back) {
  s21::list<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.pop_back();
  std_list.pop_back();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(list, Iterator_Begin) {
  s21::list<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
}

TEST(list, Iterator_BeginPlusAndMinus) {
  s21::list<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  --our_it;
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(list, Iterator_End_Last) {
  s21::list<int> our_list({1, 2, 3});
  std::list<int> std_list({1, 2, 3});
  s21::list<int>::iterator our_it;
  our_it = our_list.end();
  --our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.end();
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(list, ConstIterator_End_Last) {
  const s21::list<int> our_list({1, 2, 3});
  const std::list<int> std_list({1, 2, 3});
  auto our_it = our_list.cend();
  --our_it;
  auto std_it = std_list.cend();
  --std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(list, ConstIterator_End_Last_2) {
  const s21::list<int> our_list({1, 2, 3});
  auto our_it = our_list.cend();
  --our_it;
  --our_it;
  --our_it;
  EXPECT_TRUE(our_list.cbegin() == our_it);
}

TEST(list, Iterator_Equals) {
  s21::list<int> first_list({1, 2, 3});
  s21::list<int>::iterator our_it_first;
  our_it_first = first_list.begin();
  s21::list<int>::iterator our_it_second;
  our_it_second = first_list.begin();
  EXPECT_TRUE(our_it_first == our_it_second);
  ++our_it_second;
  EXPECT_TRUE(our_it_first != our_it_second);
}

TEST(list, insert) {
  s21::list<int> our_list;
  std::list<int> std_list;
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  our_list.insert(our_it, 5);
  std_list.insert(std_it, 5);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.insert(our_it, 7);
  std_list.insert(std_it, 7);
  our_list.insert(our_it, 9);
  std_list.insert(std_it, 9);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(list, erase1) {
  s21::list<int> our_list({1, 2, 3, 4, 5});
  std::list<int> std_list({1, 2, 3, 4, 5});
  our_list.erase(our_list.begin());
  std_list.erase(std_list.begin());
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  s21::list<int>::iterator our_it;
  our_it = our_list.begin();
  ++our_it;
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  ++std_it;
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}
TEST(list, erase2) {
  s21::list<int> s21_list_1 = {'a', 'c', 'd'};
  s21::list<int> s21_list_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_list_2.begin();
  ++it;
  s21_list_2.erase(it);
  auto it1 = s21_list_1.begin();
  auto it2 = s21_list_2.begin();
  while (it1 != s21_list_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_list_1.size(), s21_list_2.size());
}

TEST(list, Splice1) {
  s21::list<int> our_list_first({1});
  s21::list<int> our_list_second({2, 3, 4, 5});
  std::list<int> std_list_first({1});
  std::list<int> std_list_second({2, 3, 4, 5});
  s21::list<int>::const_iterator our_it = our_list_first.cbegin();
  std::list<int>::iterator std_it = std_list_first.begin();
  our_list_first.splice(our_it, our_list_second);
  std_list_first.splice(std_it, std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
}

TEST(list, Splice2) {
  s21::list<int> myList1 = {1, 2, 3};
  s21::list<int> myList2 = {4, 5};
  myList1.splice(myList1.cend(), myList2);
  EXPECT_EQ(myList1.size(), 5);
  EXPECT_EQ(myList2.empty(), true);
}

TEST(listTest, Splice3) {
  s21::list<int> myList1;
  s21::list<int> myList2 = {1, 2, 3, 4};
  myList1.splice(myList1.cbegin(), myList2);
  EXPECT_EQ(myList1.size(), 4);
  EXPECT_EQ(myList2.empty(), true);
}

TEST(listTest, Splice4) {
  s21::list<int> myList1 = {10, 11, 12, 32};
  s21::list<int> myList2 = {1, 2, 3, 4};
  auto it = myList1.cbegin();
  it++;
  it++;
  myList1.splice(it, myList2);
  EXPECT_EQ(myList1.size(), 8);
  EXPECT_EQ(myList2.empty(), true);
}

TEST(list, Merge) {
  s21::list<int> our_list_first({1});
  s21::list<int> our_list_second({2, 3, 4, 5});
  std::list<int> std_list_first({1});
  std::list<int> std_list_second({2, 3, 4, 5});
  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(list, Reverse) {
  s21::list<int> our_list({1, 2, 3, 4, 5});
  std::list<int> std_list({1, 2, 3, 4, 5});
  our_list.reverse();
  std_list.reverse();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(list, Unique) {
  s21::list<int> our_list({1, 2, 2, 3, 3});
  std::list<int> std_list({1, 2, 2, 3, 3});
  s21::list<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.unique();
  std_list.unique();
  our_it = our_list.begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(list, Sort) {
  s21::list<int> our_list({2, 4, 1, 3, 5});
  std::list<int> std_list({2, 4, 1, 3, 5});
  s21::list<int>::iterator our_it;
  std::list<int>::iterator std_it;
  our_list.sort();
  std_list.sort();
  our_it = our_list.begin();
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
  ++our_it;
  ++std_it;
  EXPECT_EQ(*our_it, *std_it);
}

TEST(list, insert_Many) {
  s21::list<int> our_list({1, 2, 3, 4, 5});
  s21::list<int>::const_iterator our_it = our_list.cbegin();
  ++our_it;
  our_list.insert_many(our_it, 7, 8, 9);
  s21::list<int>::iterator our_it2 = our_list.begin();
  EXPECT_EQ(*our_it2, 1);
  ++our_it2;
  EXPECT_EQ(*our_it2, 7);
  ++our_it2;
  EXPECT_EQ(*our_it2, 8);
  ++our_it2;
  EXPECT_EQ(*our_it2, 9);
  ++our_it2;
  EXPECT_EQ(*our_it2, 2);
}

TEST(list, insert_Many_Back) {
  s21::list<int> our_list({1, 2, 3, 4, 5});
  s21::list<int>::iterator our_it;
  our_list.insert_many_back(7, 8, 9);
  our_it = our_list.end();
  --our_it;
  EXPECT_EQ(*our_it, 9);
  --our_it;
  EXPECT_EQ(*our_it, 8);
  --our_it;
  EXPECT_EQ(*our_it, 7);
  --our_it;
  EXPECT_EQ(*our_it, 5);
  --our_it;
  EXPECT_EQ(*our_it, 4);
}

TEST(list, insert_Many_front) {
  s21::list<int> our_list({1, 2, 3, 4, 5});
  s21::list<int>::iterator our_it;
  our_list.insert_many_front(7, 8, 9);
  our_it = our_list.begin();
  EXPECT_EQ(*our_it, 7);
  ++our_it;
  EXPECT_EQ(*our_it, 8);
  ++our_it;
  EXPECT_EQ(*our_it, 9);
  ++our_it;
  EXPECT_EQ(*our_it, 1);
  ++our_it;
  EXPECT_EQ(*our_it, 2);
}

TEST(list, MaxSize) {
  s21::list<int> l1({1, 2, 3, 4, 5});
  std::list<int> l2({1, 2, 3, 4, 5});
  EXPECT_EQ(l1.max_size(), l2.max_size());
}

TEST(list, ListConstIterator) {
  const s21::list<int> l({1, 2, 3});
  s21::list<int>::ListConstIterator it;
  it = l.cbegin();
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(list, ListIterator) {
  s21::list<int> l({1, 2, 3});
  s21::list<int>::ListIterator it;
  it = l.begin();
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}