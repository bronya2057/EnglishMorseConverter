#include "EnglishMorseMapper.hpp"
#include "BidirectionalMapper.hpp"

#include <QRegularExpression>
#include <QDebug>

EnglishMorseMapper::EnglishMorseMapper(QObject *parent)
    : QObject(parent)
{
}

void EnglishMorseMapper::requestTranslateInput(const QString& inputText)
{
    QString result;

    QRegularExpression englishTokenRegex{QStringLiteral("^[A-Za-z]+")};
    QRegularExpression morseTokenRegex{QStringLiteral("^[.-]+")};

    qDebug() << "Input:" << inputText;

    m_convertedText = result;

    emit textConverted(m_convertedText);
}