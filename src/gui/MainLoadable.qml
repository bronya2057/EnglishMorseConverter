import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import EnglishMorseMapper

Rectangle {
    width: 1024
    height: 768
    border.color: "red"

    EnglishMorseMapper {
        id: _englishMorseMapper
    }

    ColumnLayout {
        id: _layout

        spacing: 50
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.centerIn: parent

        Label {
            text: "Enter Input in English or Morse code:"
            font.pixelSize: internal.fontPixelSize
        }

        TextField {
            id: _textInput

            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: internal.preferredWidth
            Layout.preferredHeight: internal.preferredHeight

            validator: internal.textValidator
            wrapMode: TextInput.Wrap
            font.pixelSize: 24

            onTextEdited: {
                _englishMorseMapper.requestTranslateInput(text);
            }
        }


        Label {
            text: "Output:"
            font.pixelSize: internal.fontPixelSize
        }

        TextField {
            id: _textOutput
            height: 100
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: internal.preferredWidth
            Layout.preferredHeight: internal.preferredHeight
            wrapMode: TextInput.Wrap
            font.pixelSize: 24
            readOnly: true
            text: _englishMorseMapper.convertedText
        }
    }

    QtObject {
        id: internal

        readonly property int preferredWidth: 800
        readonly property int preferredHeight: 200
        readonly property int fontPixelSize: 24
        readonly property RegularExpressionValidator textValidator: RegularExpressionValidator {regularExpression: /^[A-Za-z .-]*$/}
    }
}
