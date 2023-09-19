#include "EnglishMorseMapper.hpp"
#include "BidirectionalMapper.hpp"
#include "TextTokenizer.hpp"

#include <QRegularExpression>
#include <QDebug>

EnglishMorseMapper::EnglishMorseMapper(QObject *parent)
    : QObject(parent)
{
}

void EnglishMorseMapper::requestTranslateInput(const QString& inputText)
{
    const QString lowerCaseInput = inputText.toLower();

    const QStringList tokensResult = TextTokenizer::getTokens(inputText);

    qDebug() << "tokensResult" << tokensResult;

    m_convertedText = tokensResult.join("");

    emit textConverted(m_convertedText);
}