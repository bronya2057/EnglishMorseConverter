#include <gtest/gtest.h>

#include "BidirectionalMorseMapper.hpp"
#include "TextTokenizer.hpp"

#include <QDebug>

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

    qDebug() << "Translated:" << translatedText;
    qDebug() << "expected:" << expectedText;

    EXPECT_EQ(translatedText, expectedText);
}

TEST_F(BidirectionalMapperTest, TranslateMorseText)
{
    QString inputString{". . .- -..."};

    const QStringList tokenizedInput = TextTokenizer::getTokens(inputString);
    const QString translatedText = m_mapper.getTranslatedText(tokenizedInput);
    const QString expectedText = "e e a b";

    qDebug() << "Translated:" << translatedText;
    qDebug() << "expected:" << expectedText;

    EXPECT_EQ(translatedText, expectedText);
}

TEST_F(BidirectionalMapperTest, TranslateMixedText)
{
    QString inputString{"He. Ar. .- -...Yu-..."};

    const QStringList tokenizedInput = TextTokenizer::getTokens(inputString);
    const QString translatedText = m_mapper.getTranslatedText(tokenizedInput);
    const QString expectedText = ".... . e .- .-. e a b -.-- ..- b";

    qDebug() << "Translated:" << translatedText;
    qDebug() << "expected:" << expectedText;
    
    EXPECT_EQ(translatedText, expectedText);
}

TEST_F(BidirectionalMapperTest, TranslateErrorText)
{
    QString inputString{"..... ............"};

    const QStringList tokenizedInput = TextTokenizer::getTokens(inputString);
    const QString translatedText = m_mapper.getTranslatedText(tokenizedInput);
    const QString expectedText = "# #";

    qDebug() << "tokenizedInput:" << tokenizedInput;
    qDebug() << "Translated:" << translatedText;
    qDebug() << "expected:" << expectedText;
    
    EXPECT_EQ(translatedText, expectedText);
}

