import QtQuick 2.0
import QtQuick.Controls 2.0

Item{
    id: customButtonItem
    enum Shape{
            Rectangle = 0,
            Triangle = 1
        }
    property color color: "#8053a2ff"
    property string text: text
    property int shape: CustomButton.Shape.Rectangle
    signal clicked();

    function opacityChooser(item){

        let pressed = 0.4
        let hovered = 0.7
        let idle = 1.0

        if (item.pressed){
            console.log('pressed')
            return pressed
        }
        if (item.entered){
            if (item.containtMouse){
                console.log('idle')
                return idle
            }
            console.log('hovered')
            return hovered
        }
        console.log('idle')
        return idle
    }
    Item{
        id: triangle
        visible: parent.shape === CustomButton.Shape.Triangle
        enabled: visible

        readonly property int left_margin: 10

        opacity: 1

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
            hoverEnabled: true
            onEntered: triangle.opacity = customButtonItem.opacityChooser(this)
            onReleased: triangle.opacity = customButtonItem.opacityChooser(this)
            onExited: triangle.opacity = 1//customButtonItem.opacityChooser(this)
            onPressed: triangle.opacity = customButtonItem.opacityChooser(this)

        }
    }

    Rectangle {
        id: rectangle
        visible: parent.shape === CustomButton.Shape.Rectangle
        enabled: visible
        property string text: customButtonItem.text

        opacity: 1

        implicitHeight: customButtonItem.height
        implicitWidth: customButtonItem.width

        //width: rectangleText.implicitWidth > customButtonItem.width ? rectangleText.implicitWidth + 10 : customButtonItem.width
        //height: rectangleText.implicitHeight > customButtonItem.height ? rectangleText.implicitHeight + 10 : customButtonItem.height

        color: "#8053a2ff"
        radius: 15

        Text {
            id: rectangleText
            text: rectangle.text
            font.pixelSize: 0.5 * rectangle.height
            anchors.centerIn: parent
        }

        MouseArea {
            id: rectangleMouseArea
            anchors.fill: parent
            onClicked:  customButtonItem.clicked() // emit
            hoverEnabled: true
            onEntered: rectangle.opacity = customButtonItem.opacityChooser(this)
            onReleased: rectangle.opacity = customButtonItem.opacityChooser(this)
            onExited: rectangle.opacity = 1//customButtonItem.opacityChooser(this)
            onPressed: rectangle.opacity = customButtonItem.opacityChooser(this)
        }
    }
}
