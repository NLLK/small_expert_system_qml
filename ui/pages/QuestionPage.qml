import QtQuick 2.0

import '../components'
import "../pageLoader.js" as PageLoaderJs
Rectangle {
    CustomButton {
        text: 'Выйти'
        shape: CustomButton.Shape.Triangle
        onClicked: mainLoader.setSource(PageLoaderJs.PagesFilePathEnum.START_PAGE)
        //anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
    }
    QuestionField{
        id: qField
        width: 600
        height: 300
        anchors.centerIn: parent
        type: QuestionField.Type.Options
        onValueChanged: console.log(this.value)
        //value: 5

        optionsListModel:  ListModel{
            ListElement{textOption: "option 1"}
            ListElement{textOption: "option 2"}
            ListElement{textOption: "option 3"}
            ListElement{textOption: "option 4"}
        }

    }
    Text{
        text: "Какой-нибудь вопрос какого-то типа?"
        font.pointSize: 40
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: qField.top
        anchors.bottomMargin: 35
    }

}
