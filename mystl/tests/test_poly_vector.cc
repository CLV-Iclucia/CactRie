//
// Created by creeper on 11/16/24.
//
#include <gtest/gtest.h>
#include <mystl/poly_vector.h>

using namespace mystl;

struct Base {
  virtual ~Base() = default;
  virtual int value() const = 0;
};

struct DerivedA : Base {
  explicit DerivedA(int v) : v(v) {}
  int value() const override { return v; }
  int v;
};

struct DerivedB : Base {
  explicit DerivedB(int v) : v(v) {}
  int value() const override { return v; }
  int v;
};

TEST(PolyVectorTest, BasicOperations) {
  poly_vector<Base> vec;

  EXPECT_TRUE(vec.empty());
  EXPECT_EQ(vec.size(), 0);

  vec.emplace_back<DerivedA>(10);
  vec.emplace_back<DerivedB>(20);

  EXPECT_FALSE(vec.empty());
  EXPECT_EQ(vec.size(), 2);

  EXPECT_EQ(vec.front()->value(), 10);
  EXPECT_EQ(vec.back()->value(), 20);

  vec.pop_back();
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec.front()->value(), 10);

  vec.pop_front();
  EXPECT_TRUE(vec.empty());
}

TEST(PolyVectorTest, PushBack) {
  poly_vector<Base> vec;
  auto derived_a = std::make_unique<DerivedA>(30);
  auto derived_b = std::make_unique<DerivedB>(40);

  vec.push_back(std::move(derived_a));
  vec.push_back(std::move(derived_b));

  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.front()->value(), 30);
  EXPECT_EQ(vec.back()->value(), 40);
}

TEST(PolyVectorTest, Iteration) {
  poly_vector<Base> vec;

  vec.emplace_back<DerivedA>(1);
  vec.emplace_back<DerivedB>(2);
  vec.emplace_back<DerivedA>(3);

  int sum = 0;
  for (auto item : vec) {
    sum += item->value();
  }
  EXPECT_EQ(sum, 6);

  sum = 0;
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    sum += (*it)->value();
  }
  EXPECT_EQ(sum, 6);

  sum = 0;
  for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
    sum += (*it)->value();
  }
  EXPECT_EQ(sum, 6);
}

TEST(PolyVectorTest, Clear) {
  poly_vector<Base> vec;

  vec.emplace_back<DerivedA>(10);
  vec.emplace_back<DerivedB>(20);

  EXPECT_FALSE(vec.empty());
  EXPECT_EQ(vec.size(), 2);

  vec.clear();

  EXPECT_TRUE(vec.empty());
  EXPECT_EQ(vec.size(), 0);
}

TEST(PolyVectorTest, MixedTypes) {
  poly_vector<Base> vec;

  vec.emplace_back<DerivedA>(5);
  vec.emplace_back<DerivedB>(10);
  vec.emplace_back<DerivedA>(15);

  EXPECT_EQ(vec.size(), 3);

  EXPECT_EQ(vec.front()->value(), 5);
  EXPECT_EQ(vec.back()->value(), 15);

  auto it = vec.begin();
  EXPECT_EQ((*it)->value(), 5);
  ++it;
  EXPECT_EQ((*it)->value(), 10);
  ++it;
  EXPECT_EQ((*it)->value(), 15);
}

TEST(PolyVectorTest, ConstIterator) {
  poly_vector<Base> vec;

  vec.emplace_back<DerivedA>(5);
  vec.emplace_back<DerivedB>(10);

  const poly_vector<Base> &const_vec = vec;
  auto it = const_vec.begin();

  EXPECT_EQ((*it)->value(), 5);
  ++it;
  EXPECT_EQ((*it)->value(), 10);
}

