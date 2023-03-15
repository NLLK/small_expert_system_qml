import QtQuick 2.0
import QtQuick.Controls 2.0

import "./components"
Rectangle {
    anchors.fill: parent

    Text {
        id: helloLabel
        text: "Приветствую!"
        font.pointSize: 48
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 60
    }

    Text {
        text: "Начнем с выбора файла для тестирования:"
        font.pointSize: 40
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: helloLabel.bottom
        anchors.topMargin: 35
    }

    CustomButton {
        text: "Выбрать файл"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
