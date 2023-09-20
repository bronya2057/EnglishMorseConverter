import QtQuick

// brief Component that allows live reloading of QML files
// usage:
// LoaderLiveControls {
//     source: "file://fullpathToQml.qml"
// }

Loader {
    id: root

    Connections {
        target: QmlFileWatcher

        function onReloaded(path) {
            let sourceTemp = source;
            root.source = ""
            root.source = sourceTemp;
        }
    }
}
