import QtQuick

Loader {
    id: root

    Connections {
        target: QmlFileWatcher

        function onReloaded(path) {
            console.error("onReloaded");
            let sourceTemp = source;
            root.source = ""
            root.source = sourceTemp;
        }
    }
}
