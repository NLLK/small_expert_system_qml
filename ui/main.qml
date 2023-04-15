import QtQuick 2.15
import QtQuick.Window 2.2
import "./pages"
import "pageLoader.js" as PageLoaderJs

Window {
    id: mainWindow
    minimumHeight: 720
    minimumWidth: 1280
    visible: true
    title: MainUiController.dataName == "" ? "Малая экспертная система": "Малая экспертная система: "+MainUiController.dataName

    Loader{
        id: mainLoader
        source: PageLoaderJs.PagesFilePathEnum.START_PAGE
        anchors.fill: parent
    }
}
