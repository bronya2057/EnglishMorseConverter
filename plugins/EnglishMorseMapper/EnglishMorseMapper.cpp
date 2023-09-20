#include "EnglishMorseMapper.hpp"
#include "TextTraits.hpp"

EnglishMorseMapper::EnglishMorseMapper(QObject *parent)
    : QObject{parent}
    , m_translatedText{}
    , m_errorInTranslation{}
    , m_morseMapper{}
{
}

void EnglishMorseMapper::requestTranslateInput(const QString& inputText)
{
    const QString lowerCaseInput = inputText.toLower();
    const QStringList tokenizedInput = TextTraits::getTokens(inputText);
    const QString translatedText = TextTraits::getTranslatedText(tokenizedInput, m_morseMapper);

    m_translatedText = translatedText;
    m_errorInTranslation = TextTraits::errorInTranslation(translatedText);

    emit textTranslated(m_translatedText);
    emit errorInTranslationOccured(m_errorInTranslation);
}