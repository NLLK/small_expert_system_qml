import QtQuick 2.0

import '../components'
import "../pageLoader.js" as PageLoaderJs
import QtQml
Rectangle {
    id: questionPage
    property string questionText: "Temp text"
    property string questionTex: "Temp text"

    property var questionsData: []
    property int numberOfQuestions: 0
    property int questionIterator: 0

    function nextQuestion(){
        if (questionIterator < numberOfQuestions - 1){ //check for last
            questionIterator += 1
            loadFieldsFromData(questionIterator)
        }
        else {
            mainLoader.setSource(PageLoaderJs.PagesFilePathEnum.RESULTS_PAGE)
        }
    }

    function createOptionsList(data){
        let outputArray = []
        data.forEach(element => {
            outputArray.push(
                             {
                                "textOption": element
                             }
            )
        });
        return outputArray
    }

    function loadFieldsFromData(iter){
        let data = questionsData[iter]

        if (data.questionType === QuestionField.Type.Plain ||
            data.questionType === QuestionField.Type.Ranges ||
            data.questionType === QuestionField.Type.Options)
        {
            qField.value = 0
            qField.type = data.questionType
            questionPage.questionText = data.questionText
        }

        switch (qField.type){
        case QuestionField.Type.Ranges:{
            qField.width = 350
            qField.height = 90
            break;
        }
        case QuestionField.Type.Plain:{
            qField.width = 600
            qField.height = 300
            qField.minimum = data.plainMinimum
            qField.maximum = data.plainMaximum
            qField.value = (qField.maximum + qField.minimum) / 2
            break;
        }
        case QuestionField.Type.Options:{
            qField.width = 600
            qField.height = 300
            qField.optionsListModel.clear()
            qField.optionsListModel.append(questionPage.createOptionsList(data.optionsOptions))
            break;
        }
        }
    }

    function setAnswerForQuestion(value){
        //console.log('answer',questionPage.questionIterator, value)
        questionsData[questionIterator].value = value
    }

    //@disable-check M16
    Component.onCompleted: {
        questionPage.numberOfQuestions = MainUiController.numberOfQuestions
//        print(MainUiController.questionsList[0].questionText)
        if  (questionPage.numberOfQuestions > 0){
            questionPage.questionsData = MainUiController.questionsList
            questionPage.loadFieldsFromData(0)
        }
        //.push({'type': 0, 'text': 'test question text', 'value': 5},
        //{'type': 1, 'text': 'test question text ranges', 'minimum': 0, 'maximum': 10},
        //{'type': 2, 'text': 'test question text options', 'options': [{'textOption':'Op1'}, {'textOption':'Op2'}, {'textOption':'Op3'}]})


    }
    CustomButton {
        text: 'Выйти'
        shape: CustomButton.Shape.Triangle
        onClicked: mainLoader.setSource(PageLoaderJs.PagesFilePathEnum.START_PAGE)
        anchors.left: parent.left
    }

    QuestionField{
        id: qField
        width: 600
        height: 300
        anchors.centerIn: parent
        type: QuestionField.Type.Plain
        onValueChanged: questionPage.setAnswerForQuestion(this.value)
    }
    Text{
        text: questionText
        font.pointSize: 40
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: qField.top
        anchors.bottomMargin: 35
    }
    CustomButton {
        text: 'Ответить'
        onClicked: {questionPage.nextQuestion()}
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: qField.bottom
        anchors.topMargin: 15

        width: 350
        height: 90
    }

}
