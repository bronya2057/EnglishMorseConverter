#include "EnglishMorseMapper.hpp"
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

    const QStringList tokenizedInput = TextTokenizer::getTokens(inputText);
    const QString translatedText = m_morseMapper.getTranslatedText(tokenizedInput);

    m_convertedText = translatedText;

    emit textConverted(m_convertedText);
}