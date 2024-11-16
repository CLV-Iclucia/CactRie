//
// Created by creeper on 11/16/24.
//
#include <gtest/gtest.h>
#include <ranges>
#include <algorithm>
#include <vector>
#include <chiisai-llvm/mystl/manager_vector.h>

using namespace llvm::mystl;

TEST(ManagerVectorTest, BasicTypeOperations) {
  manager_vector<int> vec;

  vec.emplace_back(10);
  vec.emplace_back(20);
  vec.emplace_back(30);

  EXPECT_EQ(*vec[0], 10);
  EXPECT_EQ(*vec[1], 20);
  EXPECT_EQ(*vec[2], 30);

  EXPECT_EQ(vec.size(), 3);
  EXPECT_FALSE(vec.empty());

  vec.erase(1);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(*vec[0], 10);
  EXPECT_EQ(*vec[1], 30);
}

struct MyClass {
  explicit MyClass(int x) : x(x) {}
  int x;
};

TEST(ManagerVectorTest, CustomTypeOperations) {
  manager_vector<MyClass> vec;

  vec.emplace_back(10);
  vec.emplace_back(20);
  vec.emplace_back(30);

  EXPECT_EQ(vec[0]->x, 10);
  EXPECT_EQ(vec[1]->x, 20);
  EXPECT_EQ(vec[2]->x, 30);

  vec[0]->x = 100;
  EXPECT_EQ(vec[0]->x, 100);

  EXPECT_EQ(vec.size(), 3);
  EXPECT_FALSE(vec.empty());

  vec.erase(1);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[0]->x, 100);
  EXPECT_EQ(vec[1]->x, 30);
}

TEST(ManagerVectorTest, InteractWithRangesAndAlgorithms) {
  manager_vector<int> vec;

  vec.emplace_back(1);
  vec.emplace_back(2);
  vec.emplace_back(3);
  vec.emplace_back(4);

  std::vector<int> transformed;
  std::for_each(vec.begin(), vec.end(), [&transformed](const auto& value) {
    transformed.push_back(*value * 2);
  });

  EXPECT_EQ(transformed, std::vector<int>({2, 4, 6, 8}));
}

TEST(ManagerVectorTest, BoundaryCases) {
  manager_vector<int> vec;

  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());

  EXPECT_THROW(vec.at(0), std::out_of_range);

  vec.emplace_back(100);
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
  EXPECT_TRUE(vec.empty());
}

