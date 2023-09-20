#include "TextTraits.hpp"
#include "BidirectionalMorseMapper.hpp"

#include <QRegularExpression>

namespace TextTraits
{

static const QString errorToken{QStringLiteral("#")};

bool isMorseToken(const QString& inputToken)
{
    static const QRegularExpression morseTokenRegex{QStringLiteral("^[.-]+")};
    return morseTokenRegex.match(inputToken).hasMatch();
}

bool isEnglishToken(const QString& inputToken)
{
    static const QRegularExpression englishTokenRegex{QStringLiteral("^[A-Za-z]+")};
    return englishTokenRegex.match(inputToken).hasMatch();
}

bool errorInTranslation(const QString& inputTranslation)
{
    return inputTranslation.contains(errorToken);
}

QString getTranslatedText(const QStringList& tokensToTranslate, const BidirectionalMorseMapper& mapper)
{    
    QStringList result;

    for (auto it = tokensToTranslate.begin(); it != tokensToTranslate.end(); ++it)
    {
        const auto& token = *it;

        const bool tokenHasErrors = !isEnglishToken(token) && !isMorseToken(token);

        if (isEnglishToken(token))
        {
            const auto& mappedToken = mapper.map(token[0]);
            result.push_back(mappedToken.isEmpty() ? errorToken : mappedToken);
        }
        else if (isMorseToken(token))
        {
            const auto& mappedToken = mapper.map(token);
            result.push_back(mappedToken.isNull() ? errorToken[0] : mappedToken);
        }

        if (it + 1 != tokensToTranslate.end() && !tokenHasErrors)
        {
            result.push_back(" ");
        }
    }

    return result.join("");
}

QStringList getTokens(const QString& inputString)
{
    QStringList tokensResult;

    const QString lowerCaseInput = inputString.toLower();

    QString tokenInProcess;

    auto morseTokenCompleteAction = [&tokenInProcess, &tokensResult](){
        tokensResult.push_back(tokenInProcess);
        tokenInProcess.clear();
    };

    for (auto&& inputToken: qAsConst(lowerCaseInput))
    {
        if (isEnglishToken(inputToken))
        {
            if (!tokenInProcess.isEmpty())
            {
                morseTokenCompleteAction();
            }

            tokensResult.push_back(inputToken);
        }
        else if (isMorseToken(inputToken))
        {
            tokenInProcess.push_back(inputToken);
        }
        else if (!tokenInProcess.isEmpty())
        {
            morseTokenCompleteAction();
        }
    }

    if (!tokenInProcess.isEmpty())
    {
       morseTokenCompleteAction();
    }

    return tokensResult;
}

} //namespace TextTraits