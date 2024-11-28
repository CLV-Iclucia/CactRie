//
// Created by creeper on 11/27/24.
//
#include <gtest/gtest.h>
#include <mystl/ref_counted.h>
using namespace mystl;

TEST(RefCounted, DefaultConstructor) {
  ref_counted<int> rc;
  EXPECT_EQ(rc.get(), nullptr);
  EXPECT_EQ(rc.use_count(), 0);
}

TEST(RefCounted, Constructor) {
  int *p = new int(42);
  ref_counted<int> rc(p);
  EXPECT_EQ(rc.get(), p);
  EXPECT_EQ(rc.use_count(), 1);
}

TEST(RefCounted, CopyConstructor) {
  int *p = new int(42);
  ref_counted<int> rc1(p);
  ref_counted<int> rc2(rc1);
  EXPECT_EQ(rc1.get(), p);
  EXPECT_EQ(rc2.get(), p);
  EXPECT_EQ(rc1.use_count(), 2);
  EXPECT_EQ(rc2.use_count(), 2);
}

TEST(RefCounted, MoveConstructor) {
  int *p = new int(42);
  ref_counted<int> rc1(p);
  ref_counted<int> rc2(std::move(rc1));
  EXPECT_EQ(rc1.get(), nullptr);
  EXPECT_EQ(rc2.get(), p);
  EXPECT_EQ(rc1.use_count(), 0);
  EXPECT_EQ(rc2.use_count(), 1);
}

TEST(RefCounted, CopyAssignment) {
  int *p = new int(42);
  ref_counted<int> rc1(p);
  int *q = new int(43);
  ref_counted<int> rc2(q);
  rc2 = rc1;
  EXPECT_EQ(rc1.get(), p);
  EXPECT_EQ(rc2.get(), p);
  EXPECT_EQ(rc1.use_count(), 2);
  EXPECT_EQ(rc2.use_count(), 2);
}


TEST(RefCounted, MoveAssignment) {
  int *p = new int(42);
  ref_counted<int> rc1(p);
  int *q = new int(43);
  ref_counted<int> rc2(q);
  rc2 = std::move(rc1);
  EXPECT_EQ(rc1.get(), nullptr);
  EXPECT_EQ(rc2.get(), p);
  EXPECT_EQ(rc1.use_count(), 0);
  EXPECT_EQ(rc2.use_count(), 1);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}