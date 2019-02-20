#include <gtest/gtest.h>

#include "example.hpp"

TEST(Dummy, example) {
  Dummy d = Dummy();
  ASSERT_TRUE(d.doSomething());
}