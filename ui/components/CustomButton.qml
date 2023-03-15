import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    property alias text: button.text

    width: 350
    height: 90

    Button{
        id: button
        background: Rectangle {
             color: "#8053a2ff"
             radius: 5
        }
        font.pointSize: 32
        anchors.fill: parent
    }

}
