#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SharedPtr.hpp"

// struct ExampleTests : public ::testing::Test
// {
//    int *x;

//    int getX()
//    {
//       return *x;
//    }

//    virtual void SetUp() override
//    {
//       x = new int(55);
//    }

//    virtual void TearDown() override
//    {
//       delete x;
//    }
// };

// TEST_F(ExampleTests, Demo)
// {
//     EXPECT_TRUE(getX());
//     EXPECT_EQ(getX(), 56);
//     EXPECT_EQ(false, true) << "Reason of fail could be written here"<< 254;
//     EXPECT_TRUE(getX());
//     EXPECT_TRUE(getX());
// }

// TEST_F(ExampleTests, Demo1)
// {
//     const int temp = getX();
//     EXPECT_TRUE(getX());
//     EXPECT_EQ(getX(), 56);
//     ASSERT_TRUE(false) << "Reason of fail could be written here"<< 254;
//     EXPECT_TRUE(getX());
//     EXPECT_TRUE(getX());
// }

TEST(FactorialTest, Zero) {
    shared_ptr_m<int> sh{new int{5}};
    EXPECT_EQ(sh, true);
    shared_ptr_m<int> s2 = sh;
}

// using testing::Eq;

// class SoundexEncoding : public testing::Test //Google Mock instantiates the fixture class once per test
// {
// public:
//    Soundex soundex;
// };