#pragma once

#include <QStringList>

class BidirectionalMorseMapper;

/**
 * @brief TextTraits namespace handles tokenization and translation of given text
 */
namespace TextTraits
{
    /**
     * @brief indicates whether error occured in input string
     * @param inputTranslation  translated text which might contain errors
     * @return true if error present
     */
    bool errorInTranslation(const QString& inputTranslation);

    /**
     * @brief gives translation for the given tokenized input
     * @param tokensToTranslate  input tokens
     * @param mapper  mapping object that will translate each token seperately
     * @return translated text
     */
    QString getTranslatedText(const QStringList& tokensToTranslate, const BidirectionalMorseMapper& mapper);

    /**
     * @brief tokenize user input
     * @param inputString  user input
     * @return user input in tokenized representation
     */
    QStringList getTokens(const QString& inputString);
}; //namespace TextTraits