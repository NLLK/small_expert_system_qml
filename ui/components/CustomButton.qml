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
    property bool enabled: true
    signal clicked();
    readonly property real enabledOpacity: 0.2

    function opacityChooser(item){
        let pressed = 0.4
        let hovered = 0.7
        let idle = 1.0

        if (item.pressed){
            return pressed
        }
        if (item.entered){
            return hovered
        }
        return idle
    }
    Item{
        id: triangle
        visible: parent.shape === CustomButton.Shape.Triangle
        readonly property int left_margin: 10

        opacity: customButtonItem.enabled ? 1 : enabledOpacity

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
            enabled: customButtonItem.enabled
            anchors.fill: parent
            onClicked: customButtonItem.enabled ? customButtonItem.clicked() : null
            hoverEnabled: true
            onEntered: !customButtonItem.enabled ? 1 : triangle.opacity = customButtonItem.opacityChooser(this)
            onReleased: !customButtonItem.enabled ? 1 : triangle.opacity = customButtonItem.opacityChooser(this)
            onExited: !customButtonItem.enabled ? 1 : triangle.opacity = 1//customButtonItem.opacityChooser(this)
            onPressed: !customButtonItem.enabled ? 1 : triangle.opacity = customButtonItem.opacityChooser(this)

        }
    }

    Rectangle {
        id: rectangle
        visible: parent.shape === CustomButton.Shape.Rectangle
        property string text: customButtonItem.text

        opacity: customButtonItem.enabled ? 1 : enabledOpacity

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
            enabled: customButtonItem.enabled
            anchors.fill: parent
            onClicked: customButtonItem.clicked()
            hoverEnabled: true
            onEntered: !customButtonItem.enabled ? 1 : rectangle.opacity = customButtonItem.opacityChooser(this)
            onReleased: !customButtonItem.enabled ? 1 : rectangle.opacity = customButtonItem.opacityChooser(this)
            onExited: !customButtonItem.enabled ? 1 : rectangle.opacity = 1//customButtonItem.opacityChooser(this)
            onPressed: !customButtonItem.enabled ? 1 : rectangle.opacity = customButtonItem.opacityChooser(this)
        }
    }
}
