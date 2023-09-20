#include "BidirectionalMorseMapper.hpp"
#include <QObject>
#include <QtQml>

/**
 * @brief EnglishMorseMapper QML plugin for getting translated text from user input.
 *        Input could be provided both in English or Morse language and supports only letters.
 */
class EnglishMorseMapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString translatedText MEMBER m_translatedText NOTIFY textTranslated)
    Q_PROPERTY(bool errorInTranslation MEMBER m_errorInTranslation NOTIFY errorInTranslationOccured)
    QML_ELEMENT
public:
    /**
    * @brief Ctor
    * @param parent optional parent parameter for Qt parent/child management
    */
    explicit EnglishMorseMapper(QObject *parent = nullptr);

public slots:
    /**
    * @brief request from QML to translate given text.
    *        Internal Q_PROPERTY fields should be filled after execution
    * @param inputText user input 
    */
    void requestTranslateInput(const QString& inputText);

signals:
    void textTranslated(const QString& translatedText);
    void errorInTranslationOccured(const bool errorInTranslation);

private:
    QString m_translatedText;
    bool m_errorInTranslation;
    BidirectionalMorseMapper m_morseMapper;
};