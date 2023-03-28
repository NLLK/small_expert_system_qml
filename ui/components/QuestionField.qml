import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: questionField
    enum Type{
        Plain = 0,
        Ranges = 1,
        Options = 2
    }

    property int type: QuestionField.Type.Plain
    property real value: 0

    Rectangle{
        visible: questionField.type === QuestionField.Type.Plain
        color: "#8053a2ff"
        radius: 15

        anchors.fill: parent
        TextField {

            width: parent.width - 15
            height: parent.height/2
            anchors.centerIn: parent
            //anchors.fill: parent
            placeholderText: "0"
            text: ""
            font.family: 'Inter'
            font.pixelSize: 32
            validator: IntValidator{bottom: 0; top: 999999}
            horizontalAlignment: TextInput.AlignHCenter
            color: "black"
            background: Item{}

            onTextChanged: { questionField.value = parseInt(text,10)}
        }
    }
    Item{
        visible: questionField.type === QuestionField.Type.Ranges
        anchors.fill: parent
        Rectangle{
            id: rangesRectangle
            color: "#8053a2ff"
            radius: 15

            anchors.top: parent.top
            implicitWidth: 350
            implicitHeight: 90

            TextField {
                id: rangesTextField
                width: parent.width - 15
                height: parent.height/2
                anchors.centerIn: parent
                placeholderText: "0"
                text: ""
                font.family: 'Inter'
                font.pixelSize: 32
                validator: DoubleValidator{bottom: 0; top: 10}
                horizontalAlignment: TextInput.AlignHCenter
                color: "black"
                background: Item{}

                onTextChanged: { questionField.value = parseFloat(text.replace(',', '.'))}
            }
            Text{
                anchors.top: rangesTextField.bottom
                anchors.topMargin: 5
            }
        }
    }


}
