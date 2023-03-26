import QtQuick 2.0
import QtQuick.Controls 2.0

import "../components"
import "../pageLoader.js" as PageLoaderJs

Rectangle {
    anchors.fill: parent

    Text {
        id: _choosenFileLabel
        text: "Выбранный файл:"
        font.pointSize: 48
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 45
    }

    Text {
        id: fileNameLabel
        text: " "
        font.pointSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: _choosenFileLabel.bottom
        anchors.topMargin: 10
    }

    Text {
        id: numberOfQuestionsLabel
        text: "Количество вопросов: "
        font.pointSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: fileNameLabel.bottom
        anchors.topMargin: 10
    }
    Text {
        id: numberOfVariantsLabel
        text: "Количество вариантов: "
        font.pointSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: numberOfQuestionsLabel.bottom
        anchors.topMargin: 10
    }
    CustomButton {
        id: startTestButton
        text: "Начать тест"

        width: 350
        height: 90

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    CustomButton {
        id: chooseAnotherFileButton
        text: "Выбрать другой файл"

        onClicked: fileDialog.open()

        width: 460
        height: 90

        anchors.top: startTestButton.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
    }
    CustomButton {
        text: 'Назад'
        shape: CustomButton.Shape.Triangle
        onClicked: mainLoader.setSource(PageLoaderJs.PagesFilePathEnum.START_PAGE)
        //anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
    }
    TestFileDialog{
        id: testFileDialog
        //onAccepted: mainLoader.setSource(PageLoaderJs.PagesFilePathEnum.START_PAGE)
    }
}
