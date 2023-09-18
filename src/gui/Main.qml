import QtQuick
import QtQuick.Window
import QMLLiveReloader

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    LoaderLiveControls {
        source: "file:///E:/Dev/QtChallenge/EnglishMorseConverter/src/gui/MainLoadable.qml"
    }
}
