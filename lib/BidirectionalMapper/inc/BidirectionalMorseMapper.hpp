#pragma once

#include <QHash>
#include <QVector>

/**
 * @brief Concrete mapper for dealing with translations between English and Morse letters
 */
class BidirectionalMorseMapper
{
public:
    /**
    * @brief Ctor
    */
    BidirectionalMorseMapper();
    
public:
    /**
    * @brief map morse string to a english character
    * @param morseString
    * @return english letter or in case of error empty QChar
    */
    QChar map(const QString& morseString) const;

    /**
    * @brief map english character to a morse string
    * @param englishCharacter
    * @return morse letter or in case of error empty QString
    */
    QString map(const QChar& englishCharacter) const;

private:
    QHash<QChar, QString> m_englishToMorse;
    QHash<QString, QChar> m_morseToEnglish;
};
