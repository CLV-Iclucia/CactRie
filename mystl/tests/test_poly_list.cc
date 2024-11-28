//
// Created by creeper on 11/16/24.
//
#include <gtest/gtest.h>
#include <memory>
#include <list>
#include <type_traits>
#include <mystl/poly_list.h>

using namespace mystl;

struct Base {
  virtual ~Base() = default;
  virtual int getValue() const = 0;
};

struct DerivedA : Base {
  explicit DerivedA(int v) : value(v) {}
  int getValue() const override { return value; }
  int value;
};

struct DerivedB : Base {
  explicit DerivedB(int v) : value(v) {}
  int getValue() const override { return value; }
  int value;
};

TEST(PolyListTest, BasicOperations) {
  poly_list<Base> list;

  list.emplace_back<DerivedA>(10);
  list.emplace_back<DerivedB>(20);

  EXPECT_EQ(list.size(), 2);
  EXPECT_FALSE(list.empty());

  list.emplace_front<DerivedA>(5);
  EXPECT_EQ(list.size(), 3);

  auto it = list.begin();
  EXPECT_EQ((*it)->getValue(), 5);
  ++it;
  EXPECT_EQ((*it)->getValue(), 10);
  ++it;
  EXPECT_EQ((*it)->getValue(), 20);

  it = list.begin();
  list.erase(it);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ((*list.begin())->getValue(), 10);

  list.clear();
  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}

TEST(PolyListTest, PushUniquePtr) {
  poly_list<Base> list;

  auto ptrA = std::make_unique<DerivedA>(30);
  list.push_back(std::move(ptrA));
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ((*list.begin())->getValue(), 30);

  auto ptrB = std::make_unique<DerivedB>(40);
  list.push_front(std::move(ptrB));
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ((*list.begin())->getValue(), 40);
}
TEST(PolyViewListTest, BasicOperations) {
  poly_view_list<Base> viewList;

  DerivedA objA(50);
  DerivedB objB(60);

  viewList.push_back<DerivedA>(&objA);
  viewList.push_back<DerivedB>(&objB);
  EXPECT_EQ(viewList.size(), 2);

  DerivedA objC(40);
  viewList.push_front<DerivedA>(&objC);
  EXPECT_EQ(viewList.size(), 3);

  auto it = viewList.begin();
  EXPECT_EQ((*it)->getValue(), 40);
  ++it;
  EXPECT_EQ((*it)->getValue(), 50);
  ++it;
  EXPECT_EQ((*it)->getValue(), 60);

  it = viewList.begin();
  viewList.erase(it);  // 删除第一个元素
  EXPECT_EQ(viewList.size(), 2);
  EXPECT_EQ((*viewList.begin())->getValue(), 50);

  viewList.clear();
  EXPECT_EQ(viewList.size(), 0);
  EXPECT_TRUE(viewList.empty());
}

TEST(PolyViewListTest, IterationAndModification) {
  poly_view_list<Base> viewList;

  DerivedA objA(70);
  DerivedB objB(80);
  viewList.push_back<DerivedA>(&objA);
  viewList.push_back<DerivedB>(&objB);

  auto it = viewList.begin();
  EXPECT_EQ((*it)->getValue(), 70);
  ++it;
  EXPECT_EQ((*it)->getValue(), 80);
  EXPECT_NE(it, viewList.end());
  ++it;
  EXPECT_EQ(it, viewList.end());
}
