import QtQuick 2.0
import QtQuick.Dialogs

FileDialog{
    onAccepted: MainUiController.filePath = selectedFile
}
