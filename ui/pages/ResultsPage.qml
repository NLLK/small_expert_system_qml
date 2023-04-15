import QtQuick 2.15
import QtQuick.Layouts 1.15

import '../components'

import '../pageLoader.js' as PageLoaderJs

Item {
    anchors.fill: parent
    Text {
        id: resultsLabel
        text: "Результаты!"
        font.pointSize: 48
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 45
    }

    ListView{
        id: resultsListView

        model: MainUiController.resultsList

        delegate:
            Rectangle{
                id: resultsListViewRectangle

                property string variant_text: modelData.variant_text
                property string variant_match: modelData.match_percentage

                radius: 15
                color: "#8053a2ff"
                height: 90
                width: parent.width

                ColumnLayout{
                    anchors.fill: parent
                    anchors.margins: 5
                    spacing: 5
                    Text {
                        text: "Вариант: "+ resultsListViewRectangle.variant_text
                        font.pointSize: 22
                    }
                    Text {

                        text: "Подходит вам на " + resultsListViewRectangle.variant_match
                        font.pointSize: 22

                    }
                }
            }

        width: 500
        height: 300

        interactive: false

        clip: true
        spacing: 10

        anchors.top: resultsLabel.bottom
        anchors.topMargin: 60
        anchors.horizontalCenter: parent.horizontalCenter
    }

    CustomButton {
        id: resultsStartAgainButton
        text: 'Пройти тест заново'
        onClicked: mainLoader.setSource(PageLoaderJs.PagesFilePathEnum.QUESTION_PAGE)

        fontSize: 40

        width: 400
        height: 90

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: resultsListView.bottom
        anchors.topMargin: 15

    }
    CustomButton {
        id: resultsBackToMainMenuButton
        text: 'В главное меню'
        onClicked: mainLoader.setSource(PageLoaderJs.PagesFilePathEnum.START_PAGE)

        width: 400
        height: 90

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: resultsStartAgainButton.bottom
        anchors.topMargin: 15

    }
    CustomButton {
        text: 'Тоже в главное меню'
        shape: CustomButton.Shape.Triangle
        onClicked: mainLoader.setSource(PageLoaderJs.PagesFilePathEnum.START_PAGE)
        anchors.left: parent.left
    }
}
