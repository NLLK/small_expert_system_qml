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
    property real minimum: 0
    property real maximum: 10

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
        implicitWidth: 500
        //implicitHeight: 90
        Rectangle{
            id: rangesRectangle
            color: "#8053a2ff"
            radius: 15

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            implicitWidth: 350
            implicitHeight: 90

            TextField {
                id: rangesTextField

                placeholderText: "0"
                text: value

                font.family: 'Inter'
                font.pixelSize: 32
                color: "black"
                background: Item{}

                validator: DoubleValidator{bottom: 0; top: 10; decimals: 2}
                onTextChanged: {
                    let value = parseFloat(text.replace(',', '.'))
                    if ((value > 10 || value < 0) && !isNaN(value)){
                        text = text.substring(0,text.length-1)
                    }
                    else
                        if (!isNaN(value)){
                            questionField.value = parseFloat(text.replace(',', '.'))
                        }
                }

                width: parent.width - 15
                height: parent.height/2

                anchors.centerIn: parent
                horizontalAlignment: TextInput.AlignHCenter
            }
            Text{
                anchors.top: rangesTextField.bottom
                anchors.topMargin: 5
            }
        }
        Item {
            id: rangesSlider

            property double maximum: 10
            //property double value:
            property double minimum:  0

            implicitWidth: 500;
            height: 100

            anchors.top: rangesRectangle.bottom
            anchors.horizontalCenter: rangesRectangle.horizontalCenter
            anchors.topMargin: 30

            Rectangle {
                id: rangesSliderLine
                x:     rangesSliderPill.width/2
                width: rangesSlider.width-(rangesSliderPill.width/2); height: 4
                radius: 0.5 * height
                color: 'black'
                anchors.verticalCenter: parent.verticalCenter
            }

            Repeater{//dots
                model: 5
                delegate:
                    Rectangle {
                        x: rangesSliderLine.x - 7.5 + ((rangesSliderLine.width) / 4) * index
                        width: 15;  height: width
                        radius: 0.5 * height
                        anchors.verticalCenter: parent.verticalCenter
                        color: '#53A2FF'
                    }
            }

            Rectangle {
                id: rangesSliderPill

                x: (rangesSliderLine.width + rangesSliderLine.x) * ((questionField.value - minimum) / (maximum - minimum))  // pixels from value
                width: 30;  height: width
                border.width: 3
                radius: 0.5 * height
                border.color: 'black'//enabled  &&  !mouseArea.pressed? '#000000': '#90000000' // disabled/pressed state
                anchors.verticalCenter: parent.verticalCenter
                color: '#53A2FF'
            }

            MouseArea {
                id: mouseArea
                readonly property int marginArea: rangesSliderPill.height
                width: rangesSliderLine.width
                height: rangesSliderLine.height + marginArea
                x: rangesSliderLine.x
                y: rangesSliderLine.y - marginArea/2

                drag {
                    target:   rangesSliderPill
                    axis:     Drag.XAxis
                    maximumX: rangesSliderLine.width + rangesSliderLine.x - rangesSliderPill.width/2
                    minimumX: rangesSliderLine.x - rangesSliderPill.width/2
                }

                onPositionChanged:  if(drag.active) rangesSlider.setPixels(rangesSliderPill.x + 0.5 * rangesSliderPill.width - rangesSliderLine.x) // drag pill
                onClicked:{
                    rangesSlider.setPixels(mouseArea.mouseX);
                    rangesSliderPill.x = mouseX - rangesSliderPill.width/2 + mouseArea.x
                }
            }

            function setPixels(pixels) {
                var value = ((maximum - minimum) / (rangesSliderLine.width)) * (pixels) + minimum // value from pixels
                questionField.value = value.toFixed(2)
            }
        }
    }

}
