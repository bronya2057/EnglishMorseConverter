import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import EnglishMorseMapper

Item {
    ColumnLayout {
        anchors.centerIn: parent
        spacing: 50
        
        Label {
            text: qsTr("Enter Input in English or space seperated Morse code:")
            font.pixelSize: internal.fontPixelSize
        }

        TextField {
            id: _textInput
            
            font.pixelSize: 24
            wrapMode: TextInput.Wrap
            validator: internal.userInputValidator

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
            
            text: _englishMorseMapper.translatedText
            font.pixelSize: 24
            wrapMode: TextInput.Wrap
            readOnly: true

            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: internal.preferredWidth
            Layout.preferredHeight: internal.preferredHeight
        }

        Label {
            text: qsTr("Errors (#) ocurred in translation")
            font.pixelSize: internal.errorfontPixelSize
            visible: _englishMorseMapper.errorInTranslation
            color: "red"
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
        readonly property int errorfontPixelSize: 20
        readonly property RegularExpressionValidator userInputValidator: RegularExpressionValidator {regularExpression: /^[A-Za-z .-]*$/}
    }
}
