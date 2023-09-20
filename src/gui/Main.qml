import QtQuick
import QtQuick.Window
import QMLLiveReloader

Window {
    width: 1024
    height: 768
    visible: true
    title: qsTr("Converter between English and Morse code")

    ConverterView {
        anchors.fill: parent
    }
}
