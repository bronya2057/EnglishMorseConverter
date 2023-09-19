import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import EnglishMorseMapper

Item {
    width: 1024
    height: 768

    ColumnLayout {
        id: _layout

        spacing: 50
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.centerIn: parent

        Label {
            text: qsTr("Enter Input in English or Morse code:")
            font.pixelSize: internal.fontPixelSize
        }

        TextField {
            id: _textInput
            
            font.pixelSize: 24
            wrapMode: TextInput.Wrap
            validator: internal.textValidator

            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: internal.preferredWidth
            Layout.preferredHeight: internal.preferredHeight
            
            onTextEdited: {
                _englishMorseMapper.requestTranslateInput(text);
            }
        }


        Label {
            text: qsTr("Output:")
            font.pixelSize: internal.fontPixelSize
        }

        TextField {
            id: _textOutput
            
            text: _englishMorseMapper.convertedText
            font.pixelSize: 24
            wrapMode: TextInput.Wrap
            readOnly: true

            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: internal.preferredWidth
            Layout.preferredHeight: internal.preferredHeight
        }
    }

    EnglishMorseMapper {
        id: _englishMorseMapper
    }
    
    QtObject {
        id: internal

        readonly property int preferredWidth: 800
        readonly property int preferredHeight: 200
        readonly property int fontPixelSize: 24
        readonly property RegularExpressionValidator textValidator: RegularExpressionValidator {regularExpression: /^[A-Za-z .-]*$/}
    }
}
