#include <gtest/gtest.h>

#include "BidirectionalMorseMapper.hpp"
#include "TextTokenizer.hpp"

class BidirectionalMapperTest : public ::testing::Test
{
protected:
   BidirectionalMorseMapper m_mapper;
};

TEST_F(BidirectionalMapperTest, BidirectionalMapperInit)
{
    QString inputString{""};
    const QStringList tokenizedInput = TextTokenizer::getTokens(inputString);
    const QString translatedText = m_mapper.getTranslatedText(tokenizedInput);

    EXPECT_EQ(translatedText, "");
}

TEST_F(BidirectionalMapperTest, TranslateEnglishText)
{
    QString inputString{"He H E "};

    const QStringList tokenizedInput = TextTokenizer::getTokens(inputString);
    const QString translatedText = m_mapper.getTranslatedText(tokenizedInput);
    const QString expectedText = ".... . .... .";

    EXPECT_EQ(translatedText, expectedText);
}

// TEST_F(BidirectionalMapperTest, TextMorseTokens)
// {
//     QString inputString{". . .- -..."};

//     const QStringList result = m_tokenizer.getTokens(inputString);
//     const QStringList expectedList{".", ".", ".-", "-..."};
//     EXPECT_EQ(result, expectedList);
// }

// TEST_F(BidirectionalMapperTest, MixedEnglishAndMorseTokens)
// {
//     QString inputString{"He. Ar. .- -...Yu-..."};

//     const QStringList result = m_tokenizer.getTokens(inputString);
//     const QStringList expectedList{"h", "e", ".", "a", "r", ".", ".-", "-...", "y", "u", "-..."};
//     EXPECT_EQ(result, expectedList);
// }