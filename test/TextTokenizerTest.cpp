#include <gtest/gtest.h>

#include "TextTokenizer.hpp"

class TextTokenizerTest : public ::testing::Test
{
protected:
};

TEST_F(TextTokenizerTest, TextTokenizerInit)
{
    QString inputString{""};
    const QStringList result = TextTokenizer::getTokens(inputString);
    const QStringList expectedList;
    EXPECT_EQ(result, expectedList);
}

TEST_F(TextTokenizerTest, TextEnglishTokens)
{
    QString inputString{"Hello H E L l o"};

    const QStringList result = TextTokenizer::getTokens(inputString);
    const QStringList expectedList{"h", "e", "l", "l", "o", "h", "e", "l", "l", "o"};
    EXPECT_EQ(result, expectedList);
}

TEST_F(TextTokenizerTest, TextMorseTokens)
{
    QString inputString{". . .- -..."};

    const QStringList result = TextTokenizer::getTokens(inputString);
    const QStringList expectedList{".", ".", ".-", "-..."};
    EXPECT_EQ(result, expectedList);
}

TEST_F(TextTokenizerTest, MixedEnglishAndMorseTokens)
{
    QString inputString{"He. Ar. .- -...Yu-..."};

    const QStringList result = TextTokenizer::getTokens(inputString);
    const QStringList expectedList{"h", "e", ".", "a", "r", ".", ".-", "-...", "y", "u", "-..."};
    EXPECT_EQ(result, expectedList);
}
