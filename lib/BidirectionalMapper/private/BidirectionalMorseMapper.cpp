
#include "BidirectionalMorseMapper.hpp"

static const QVector<QPair<QChar, QString>> englishMorseMapping = {
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

BidirectionalMorseMapper::BidirectionalMorseMapper()
{ 
    for (auto&& mappingPair : englishMorseMapping)
    {
        m_englishToMorse[mappingPair.first] = mappingPair.second;
        m_morseToEnglish[mappingPair.second] = mappingPair.first;
    } 
}

QChar BidirectionalMorseMapper::map(const QString& morseString) const
{
    return m_morseToEnglish.find(morseString) != m_morseToEnglish.end() ? m_morseToEnglish[morseString] : QChar{};
}

QString BidirectionalMorseMapper::map(const QChar& englishCharacter) const
{
    return m_englishToMorse.find(englishCharacter) != m_englishToMorse.end() ? m_englishToMorse[englishCharacter] : QString{};
}
