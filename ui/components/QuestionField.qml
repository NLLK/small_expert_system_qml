import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQml
import './'
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

    property ListModel optionsListModel
    Rectangle{
        visible: questionField.type === QuestionField.Type.Plain
        color: "#8053a2ff"
        radius: 15

        anchors.fill: parent
        TextField {

            width: parent.width - 15
            height: parent.height/2
            anchors.centerIn: parent
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
        Rectangle{
            id: rangesRectangle
            border.color: "#8053a2ff"
            border.width: 5
            radius: 15

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            implicitWidth: 350
            implicitHeight: 90

            TextField {
                id: rangesTextField

                placeholderText: "0"
                text: questionField.value + ''

                font.family: 'Inter'
                font.pixelSize: 32
                color: "black"
                background: Item{}

                //validator: RegularExpressionValidator{regularExpression: /[+-]?([0-9]*[.])?[0-9]+/}//DoubleValidator{bottom: 0; top: 10; decimals: 2; }//locale: "en_US"
                onTextChanged: {
                    let value = parseFloat(text)
                    if ((value > 10 || value < 0) && !isNaN(value)){
                        text = text.substring(0,text.length-1)
                    }
                    else
                        if (!isNaN(value)){
                            questionField.value = parseFloat(text)
                            rangesSlider.value = questionField.value
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
            property double minimum:  0
            property real value
            implicitWidth: 500
            height: 100

            anchors.top: rangesRectangle.bottom
            anchors.horizontalCenter: rangesRectangle.horizontalCenter
            anchors.topMargin: 30

            onValueChanged: {
                rangesSliderPill.x = rangesSlider.setValue(rangesSlider.value)
            }

            Rectangle {
                id: rangesSliderLine
                width: rangesSlider.width
                height: 4
                radius: 0.5 * height
                color: 'black'
                anchors.verticalCenter: parent.verticalCenter
            }

            readonly property real dotWidth: 15
            Repeater{//dots
                id: rangesSliderDotsRepeater
                model: 5
                delegate:
                    Rectangle {
                        x:  ((rangesSliderLine.width) / (rangesSliderDotsRepeater.model-1)) * index - rangesSlider.dotWidth/2
                        width: rangesSlider.dotWidth;  height: width
                        radius: 0.5 * height
                        anchors.verticalCenter: parent.verticalCenter
                        color: '#53A2FF'
                    }
            }
            Rectangle {
                id: rangesSliderPill

                x: rangesSlider.setValue(rangesSlider.value)// pixels from value
                width: 30;  height: width
                border.width: 3
                radius: 0.5 * height
                border.color: 'black'
                anchors.verticalCenter: parent.verticalCenter
                color: '#53A2FF'
            }

            MouseArea {
                id: mouseArea
                readonly property int marginArea: rangesSliderPill.height
                width: rangesSliderLine.width
                height: rangesSliderLine.height + marginArea
                y: rangesSliderLine.y - marginArea/2

                drag {
                    target:   rangesSliderPill
                    axis:     Drag.XAxis
                    maximumX: rangesSliderLine.width - rangesSliderPill.width/2
                    minimumX: -rangesSliderPill.width/2
                }

                onPositionChanged:  if(drag.active) rangesSlider.setPixels(rangesSliderPill.x) // drag pill
                onClicked:{
                    rangesSlider.setPixels(mouseArea.mouseX - rangesSliderPill.width/2);
                    rangesSliderPill.x = mouseArea.mouseX - rangesSliderPill.width/2
                }
            }

            function setValue(__value){
                return ((rangesSliderLine.width)/(maximum - minimum))*(__value - minimum) - rangesSliderPill.width/2
            }

            function setPixels(pixels) {
                var value = ((maximum - minimum) / (rangesSliderLine.width)) * (pixels + rangesSliderPill.width/2) + minimum  // value from pixels
                if (value > maximum) value = maximum
                if (value < minimum) value = minimum
                questionField.value = value.toFixed(2)
                rangesTextField.text = questionField.value.toString()
                rangesTextField.focus = false
            }

            Text {
                id: rangesSliderMinimumLabel
                text: 'Нет'
                anchors.horizontalCenter: rangesSliderLine.left
                anchors.top: rangesSliderLine.bottom
                anchors.topMargin: 15
                font.family: 'Inter'
                font.pixelSize: 32
                color: "black"
            }
            Text {
                id: rangesSliderIntermediateLabel
                text: 'Наверное'
                anchors.horizontalCenter: rangesSliderLine.horizontalCenter
                anchors.top: rangesSliderLine.bottom
                anchors.topMargin: 15
                font.family: 'Inter'
                font.pixelSize: 32
                color: "black"
            }
            Text {
                id: rangesSliderMaximumLabel
                text: 'Да'
                anchors.horizontalCenter: rangesSliderLine.right
                anchors.top: rangesSliderLine.bottom
                anchors.topMargin: 15
                font.family: 'Inter'
                font.pixelSize: 32
                color: "black"
            }
        }
    }

    Item{
        visible: questionField.type === QuestionField.Type.Options
        anchors.fill: parent

        ListView {
            id: optionsListView

            model: optionsListModel
            delegate: CustomButton{
                width: ListView.view.width
                height: 90
                text: textOption
                onClicked: {
                    optionsListView.currentIndex = index
                    questionField.value = index
                }
            }
            clip: true
            spacing: 5
            highlightMoveDuration: 200
            highlight: Rectangle { color: "lightsteelblue"; radius: 15 }
            //focus: true

            anchors.fill: parent
        }


    }
}
