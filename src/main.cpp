#include <QGuiApplication>
#include <QtQml/qqmlextensionplugin.h>
#include "FileWatcher.h"

Q_IMPORT_QML_PLUGIN(QMLLiveReloaderPlugin)
Q_IMPORT_QML_PLUGIN(EnglishMorseMapperPlugin)

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    
    engine.addImportPath(":/obrodskyi/imports");
    const QUrl url(u"qrc:/obrodskyi/imports/EnglishMorseConverter/gui/Main.qml"_qs);
    
    QmlLiveReload::initFileWatcher(&engine, qgetenv("QML_LIVE_RELOADER_WATCH_PATH"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
