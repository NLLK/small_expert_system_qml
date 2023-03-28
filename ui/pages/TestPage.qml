import QtQuick 2.0

import  '../components'

QuestionField{
    id: qField
    width: 600
    height: 300
    anchors.centerIn: parent
    type: QuestionField.Type.Ranges
    onValueChanged: console.log(this.value)
   // value: 5
}
