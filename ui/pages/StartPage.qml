import QtQuick 2.0
import QtQuick.Controls 2.0

import "../components"
import "../pageLoader.js" as PageLoaderJs

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
        width: 350
        height: 90

        onClicked: testFileDialog.open()//mainLoader.setSource(PageLoaderJs.PagesFilePathEnum.FILE_DIALOG_PAGE)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    TestFileDialog{
        id: testFileDialog
        onAccepted:mainLoader.setSource(PageLoaderJs.PagesFilePathEnum.SHOW_CHOOSEN_FILE_PAGE)
    }
    Text{
        text: "Универсальная Малая Экспертная система\nРазработано Артемом Бабановым\nbabanov-artem@yandex.ru"
        font.pointSize: 20
        color: "#28000000"
        horizontalAlignment: Text.AlignHCenter

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 10
    }
}
