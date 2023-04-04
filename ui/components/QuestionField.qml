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
    onValueChanged: {
        if (type === QuestionField.Type.plain){
            console.log('value', value)
        }
    }

    property ListModel optionsListModel: ListModel{}

    Loader{
        anchors.fill: parent
        sourceComponent: {
            switch (questionField.type){
            case QuestionField.Type.Plain:
                return plainComponent
            case QuestionField.Type.Ranges:
                return rangesComponent
            case QuestionField.Type.Options:
                return optionsComponent
            }
        }
    }
    Component{
        id: rangesComponent
        Rectangle{
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
    }

    Component{
        id: plainComponent
        Item{
            visible: questionField.type === QuestionField.Type.Plain
            anchors.fill: parent
            implicitWidth: 500
            Rectangle{
                id: plainRectangle
                border.color: "#8053a2ff"
                border.width: 5
                radius: 15

                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                implicitWidth: 350
                implicitHeight: 90

                TextField {
                    id: plainTextField

                    placeholderText: "0"
                    text: questionField.value + ''

                    font.family: 'Inter'
                    font.pixelSize: 32
                    color: "black"
                    background: Item{}

                    onTextChanged: {
                        let value = parseFloat(text)
                        if ((value > 10 || value < 0) && !isNaN(value)){
                            text = text.substring(0,text.length-1)
                        }
                        else
                            if (!isNaN(value)){
                                questionField.value = parseFloat(text)
                                plainSliderPill.x = plainSlider.setValue(questionField.value)
                            }
                    }

                    width: parent.width - 15
                    height: parent.height/2

                    anchors.centerIn: parent
                    horizontalAlignment: TextInput.AlignHCenter
                }
                Text{
                    anchors.top: plainTextField.bottom
                    anchors.topMargin: 5
                }
            }
            Item {
                id: plainSlider

                property double maximum: 10
                property double minimum:  0

                implicitWidth: 500
                height: 100

                anchors.top: plainRectangle.bottom
                anchors.horizontalCenter: plainRectangle.horizontalCenter
                anchors.topMargin: 30

                Rectangle {
                    id: plainSliderLine
                    width: plainSlider.width
                    height: 4
                    radius: 0.5 * height
                    color: 'black'
                    anchors.verticalCenter: parent.verticalCenter
                }

                readonly property real dotWidth: 15
                Repeater{//dots
                    id: plainSliderDotsRepeater
                    model: 5
                    delegate:
                        Rectangle {
                            x:  ((plainSliderLine.width) / (plainSliderDotsRepeater.model-1)) * index - plainSlider.dotWidth/2
                            width: plainSlider.dotWidth;  height: width
                            radius: 0.5 * height
                            anchors.verticalCenter: parent.verticalCenter
                            color: '#53A2FF'
                        }
                }
                Rectangle {
                    id: plainSliderPill

                    x: plainSlider.setValue(questionField.value)// pixels from value
                    width: 30;  height: width
                    border.width: 3
                    radius: 0.5 * height
                    border.color: 'black'
                    anchors.verticalCenter: parent.verticalCenter
                    color: '#53A2FF'
                }

                MouseArea {
                    id: mouseArea
                    readonly property int marginArea: plainSliderPill.height
                    width: plainSliderLine.width
                    height: plainSliderLine.height + marginArea
                    y: plainSliderLine.y - marginArea/2

                    drag {
                        target:   plainSliderPill
                        axis:     Drag.XAxis
                        maximumX: plainSliderLine.width - plainSliderPill.width/2
                        minimumX: -plainSliderPill.width/2
                    }

                    onPositionChanged:  if(drag.active) plainSlider.setPixels(plainSliderPill.x) // drag pill
                    onClicked:{
                        plainSlider.setPixels(mouseArea.mouseX - plainSliderPill.width/2);
                        plainSliderPill.x = mouseArea.mouseX - plainSliderPill.width/2
                    }
                }

                function setValue(__value){
                    return ((plainSliderLine.width)/(maximum - minimum))*(__value - minimum) - plainSliderPill.width/2
                }

                function setPixels(pixels) {
                    var value = ((maximum - minimum) / (plainSliderLine.width)) * (pixels + plainSliderPill.width/2) + minimum  // value from pixels
                    if (value > maximum) value = maximum
                    if (value < minimum) value = minimum
                    questionField.value = value.toFixed(2)
                    plainTextField.text = questionField.value.toString()
                    plainTextField.focus = false
                }

                Text {
                    id: plainSliderMinimumLabel
                    text: 'Нет'
                    anchors.horizontalCenter: plainSliderLine.left
                    anchors.top: plainSliderLine.bottom
                    anchors.topMargin: 15
                    font.family: 'Inter'
                    font.pixelSize: 32
                    color: "black"
                }
                Text {
                    id: plainSliderIntermediateLabel
                    text: 'Наверное'
                    anchors.horizontalCenter: plainSliderLine.horizontalCenter
                    anchors.top: plainSliderLine.bottom
                    anchors.topMargin: 15
                    font.family: 'Inter'
                    font.pixelSize: 32
                    color: "black"
                }
                Text {
                    id: plainSliderMaximumLabel
                    text: 'Да'
                    anchors.horizontalCenter: plainSliderLine.right
                    anchors.top: plainSliderLine.bottom
                    anchors.topMargin: 15
                    font.family: 'Inter'
                    font.pixelSize: 32
                    color: "black"
                }
            }
        }
    }

    Component{
        id: optionsComponent
        Item{
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
                anchors.fill: parent
            }
        }
    }
}
