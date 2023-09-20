#include <gtest/gtest.h>

#include "BidirectionalMorseMapper.hpp"
#include "TextTraits.hpp"

#include <QDebug>

class BidirectionalMapperTest : public ::testing::Test
{
protected:
   BidirectionalMorseMapper m_mapper;
};

TEST_F(BidirectionalMapperTest, BidirectionalMapperInit)
{
    QString inputString{""};
    const QStringList tokenizedInput = TextTraits::getTokens(inputString);
    const QString translatedText = TextTraits::getTranslatedText(tokenizedInput, m_mapper);

    EXPECT_EQ(translatedText, "");
}

TEST_F(BidirectionalMapperTest, TranslateEnglishText)
{
    QString inputString{"He H E "};

    const QStringList tokenizedInput = TextTraits::getTokens(inputString);
    const QString translatedText = TextTraits::getTranslatedText(tokenizedInput, m_mapper);
    const QString expectedText = ".... . .... .";

    qDebug() << "Translated:" << translatedText;
    qDebug() << "expected:" << expectedText;

    EXPECT_EQ(translatedText, expectedText);
}

TEST_F(BidirectionalMapperTest, TranslateMorseText)
{
    QString inputString{". . .- -..."};

    const QStringList tokenizedInput = TextTraits::getTokens(inputString);
    const QString translatedText = TextTraits::getTranslatedText(tokenizedInput, m_mapper);
    const QString expectedText = "e e a b";

    qDebug() << "Translated:" << translatedText;
    qDebug() << "expected:" << expectedText;

    EXPECT_EQ(translatedText, expectedText);
}

TEST_F(BidirectionalMapperTest, TranslateMixedText)
{
    QString inputString{"He. Ar. .- -...Yu-..."};

    const QStringList tokenizedInput = TextTraits::getTokens(inputString);
    const QString translatedText = TextTraits::getTranslatedText(tokenizedInput, m_mapper);
    const QString expectedText = ".... . e .- .-. e a b -.-- ..- b";

    qDebug() << "Translated:" << translatedText;
    qDebug() << "expected:" << expectedText;
    
    EXPECT_EQ(translatedText, expectedText);
}

TEST_F(BidirectionalMapperTest, TranslateErrorText)
{
    QString inputString{"..... ............"};

    const QStringList tokenizedInput = TextTraits::getTokens(inputString);
    const QString translatedText = TextTraits::getTranslatedText(tokenizedInput, m_mapper);
    const QString expectedText = "# #";

    qDebug() << "tokenizedInput:" << tokenizedInput;
    qDebug() << "Translated:" << translatedText;
    qDebug() << "expected:" << expectedText;
    
    EXPECT_EQ(translatedText, expectedText);
}

TEST_F(BidirectionalMapperTest, TemplatedVersion)
{
    const QVector<QPair<QChar, QString>> englishMorseMapping = {
        {'a', QStringLiteral(".-")},
        {'b', QStringLiteral("-...")},
        {'c', QStringLiteral("-.-.")},
        {'d', QStringLiteral("-..")},
        {'e', QStringLiteral(".")},
        {'f', QStringLiteral("..-.")},
        {'g', QStringLiteral("--.")},
        {'h', QStringLiteral("....")},
        {'i', QStringLiteral("..")},
        {'j', QStringLiteral(".---")},
        {'k', QStringLiteral("-.-")},
        {'l', QStringLiteral(".-..")},
        {'m', QStringLiteral("--")},
        {'n', QStringLiteral("-.")},
        {'o', QStringLiteral("---")},
        {'p', QStringLiteral(".--.")},
        {'q', QStringLiteral("--.-")},
        {'r', QStringLiteral(".-.")},
        {'s', QStringLiteral("...")},
        {'t', QStringLiteral("-")},
        {'u', QStringLiteral("..-")},
        {'v', QStringLiteral("...-")},
        {'w', QStringLiteral(".--")},
        {'x', QStringLiteral("-..-")},
        {'y', QStringLiteral("-.--")},
        {'z', QStringLiteral("--..")}
    };
    TBidirectionalMapper<QChar, QString> mBidirectionalMap {englishMorseMapping};
    EXPECT_EQ(mBidirectionalMap.map('a'), ".-");
    EXPECT_EQ(mBidirectionalMap.map(".-"), 'a');
}

TEST_F(BidirectionalMapperTest, TemplatedVersionInt)
{
    const QVector<QPair<int, float>> englishMorseMapping = {
        {25, 33.0f},
        {77, 55.0f},
    };
    TBidirectionalMapper<int, float> mBidirectionalMap {englishMorseMapping};
    EXPECT_EQ(mBidirectionalMap.map(25), 33.0f);
    EXPECT_EQ(mBidirectionalMap.map(55.0f), 77);
}