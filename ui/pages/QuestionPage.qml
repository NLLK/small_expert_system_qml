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
        width: 350
        height: 90
        anchors.centerIn: parent
        type: QuestionField.Type.Ranges
        onValueChanged: console.log(this.value)
    }
    Text{
        text: "Какой-нибудь вопрос какого-то типа?"
        font.pointSize: 40
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: qField.top
        anchors.bottomMargin: 35
    }

}
