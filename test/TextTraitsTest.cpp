#include <gtest/gtest.h>

#include "TextTraits.hpp"

TEST(TextTraitsTest, TextTraitsInit)
{
    QString inputString{""};
    const QStringList result = TextTraits::getTokens(inputString);
    const QStringList expectedList;
    EXPECT_EQ(result, expectedList);
}

TEST(TextTraitsTest, TextEnglishTokens)
{
    QString inputString{"Hello H E L l o"};

    const QStringList result = TextTraits::getTokens(inputString);
    const QStringList expectedList{"h", "e", "l", "l", "o", "h", "e", "l", "l", "o"};
    EXPECT_EQ(result, expectedList);
}

TEST(TextTraitsTest, TextMorseTokens)
{
    QString inputString{". . .- -..."};

    const QStringList result = TextTraits::getTokens(inputString);
    const QStringList expectedList{".", ".", ".-", "-..."};
    EXPECT_EQ(result, expectedList);
}

TEST(TextTraitsTest, MixedEnglishAndMorseTokens)
{
    QString inputString{"He. Ar. .- -...Yu-..."};

    const QStringList result = TextTraits::getTokens(inputString);
    const QStringList expectedList{"h", "e", ".", "a", "r", ".", ".-", "-...", "y", "u", "-..."};
    EXPECT_EQ(result, expectedList);
}
