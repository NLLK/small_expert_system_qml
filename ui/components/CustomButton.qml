import QtQuick 2.0
import QtQuick.Controls 2.0

Item{
    id: customButtonItem
    enum Shape{
            Rectangle = 0,
            Triangle = 1
        }
    property color color: "#8053a2ff"
    property string text: text//    property int width: 350
    //    property int height: 90
    property int shape: CustomButton.Shape.Rectangle
    signal clicked();



    Item{
        id: triangle
        visible: parent.shape === CustomButton.Shape.Triangle
        enabled: visible

        readonly property int left_margin: 10

        opacity: visible && !triangleMouseArea.pressed? 1: 0.4

        width: triangleImage.width + triangleText.width + triangle.left_margin
        height: triangleImage.height + triangleText.height + triangle.left_margin
        Image {
            id: triangleImage
            source: "qrc:/ui/media/Triangle.png"

        }
        Text{
            id: triangleText
            text: customButtonItem.text
            font.family: 'Inter'
            font.pixelSize: 24
            color: 'black'

            anchors.verticalCenter: triangleImage.verticalCenter
            anchors.left: triangleImage.right
            anchors.leftMargin: triangle.left_margin

        }

        MouseArea {
            id: triangleMouseArea
            anchors.fill: parent
            onClicked:  customButtonItem.clicked() // emit
        }
    }



    Rectangle {
        id: root
        visible: parent.shape === CustomButton.Shape.Rectangle
        enabled: visible
        property string text: customButtonItem.text

        opacity: visible && !rectangleMouseArea.pressed? 1: 0.3

        implicitHeight: customButtonItem.height
        implicitWidth: customButtonItem.width

        //width: rectangleText.implicitWidth > customButtonItem.width ? rectangleText.implicitWidth + 10 : customButtonItem.width
        //height: rectangleText.implicitHeight > customButtonItem.height ? rectangleText.implicitHeight + 10 : customButtonItem.height

        color: "#8053a2ff"
        radius: 15

        Text {
            id: rectangleText
            text: root.text
            font.pixelSize: 0.5 * root.height
            anchors.centerIn: parent
        }

        MouseArea {
            id: rectangleMouseArea
            anchors.fill: parent
            onClicked:  customButtonItem.clicked() // emit
        }
    }

}


//Item {
//    enum ShapeEnum{
//        Rectangle = 0,
//        Triangle = 1
//    }
//    property alias text: button.text
//    property alias button: button
//    property int shape: CustomButton.ShapeEnum.Rectangle
//    property bool isTriagnle: shape === CustomButton.ShapeEnum.Triangle

//    Button{
//        id: button
//        background: isTriagnle ? triangle : rect1
//        font.pointSize: 32
//        flat: true
//        anchors.fill: parent
//        highlighted: false
//    }

//    Rectangle {
//        readonly property color colorIdle: "#8053a2ff"
//        readonly property color colorHovered: "#ffffff"
//        readonly property color colorDown: "#000000"

//        id: rect1
//        color: rect1.colorIdle//colorChooser(button)
//        radius: 5

////        function colorChooser(btn){
////            if (btn.hovered){
////                return rect.colorHovered
////            }
////            else if (btn.down){
////                return rect.colorDown
////            }
////            else return rect.colorIdle
////        }

////        ColorAnimation {
////            from: colorIdle
////            to: button.hovered ? rect.colorHovered : button.down ? rect.colorDown : rect.colorIdle
////            duration: 200
////            running: button.hovered || button.down
////        }
//    }
//    Image {
//        id: triangle
//        visible: isTriagnle
//        source: "qrc:/ui/media/Triangle.png"
//    }
//}
