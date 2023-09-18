#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/qqmlextensionplugin.h>
#include "FileWatcher.h"

Q_IMPORT_QML_PLUGIN(QMLLiveReloaderPlugin)

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    
    engine.addImportPath(":/obrodskyi/imports");
    const QUrl url(u"qrc:/obrodskyi/imports/EnglishMorseConverter/gui/Main.qml"_qs);
    QmlLiveReload::initFileWatcher(&engine, "E:/Dev/QtChallenge/EnglishMorseConverter/src/gui");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}