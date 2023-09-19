#include <QObject>
#include <QtQml>

class EnglishMorseMapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString convertedText MEMBER m_convertedText NOTIFY textConverted)
    QML_ELEMENT

public:
    explicit EnglishMorseMapper(QObject *parent = nullptr);

public slots:
    void requestTranslateInput(const QString& inputText);

signals:
    void textConverted(const QString& convertedText);

private:
    QString m_convertedText;
};