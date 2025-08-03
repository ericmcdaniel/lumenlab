#include <gtest/gtest.h>

TEST(Core, WorkingUnitTest_Test)
{
  EXPECT_TRUE(true);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  return 0;
}
