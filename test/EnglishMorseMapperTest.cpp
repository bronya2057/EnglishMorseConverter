#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "BidirectionalMapper.hpp"

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

TEST(BidirectionalMapper, BidirectionalMapperInit)
{
   BidirectionalMapper mapper;
   EXPECT_EQ(mapper.getValue(), 5);
}

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

// TEST(FactorialTest, Zero) {
//   EXPECT_EQ(1, 1);
// }

// using testing::Eq;

// class SoundexEncoding : public testing::Test //Google Mock instantiates the fixture class once per test
// {
// public:
//    Soundex soundex;
// };

// TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord)
// {
//    EXPECT_THAT(soundex.encode("Ab"), Eq("A100"));
// }

// TEST_F(SoundexEncoding, DISABLED_PadsWithZerosToEnsureThreeDigits)
// {
//    ASSERT_THAT(soundex.encode("I"), Eq("I000"));
// }