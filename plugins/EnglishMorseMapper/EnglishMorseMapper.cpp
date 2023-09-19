#include "EnglishMorseMapper.hpp"
#include "TextTraits.hpp"

#include <QRegularExpression>
#include <QDebug>

EnglishMorseMapper::EnglishMorseMapper(QObject *parent)
    : QObject(parent)
{
}

void EnglishMorseMapper::requestTranslateInput(const QString& inputText)
{
    const QString lowerCaseInput = inputText.toLower();

    const QStringList tokenizedInput = TextTraits::getTokens(inputText);
    const QString translatedText = TextTraits::getTranslatedText(tokenizedInput, m_morseMapper);

    m_convertedText = translatedText;

    emit textConverted(m_convertedText);
}