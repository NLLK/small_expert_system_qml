import QtQuick 2.15
import QtQuick.Window 2.2
import "./pages"
import "pageLoader.js" as PageLoaderJs
Window {
    minimumHeight: 720
    minimumWidth: 1280
    visible: true
    title: qsTr("Экспертная система \"ПК-мастер\"")

    Loader{
        id: mainLoader
        source: PageLoaderJs.PagesFilePathEnum.START_PAGE //PageLoaderJs.PagesFilePathEnum.SHOW_CHOOSEN_FILE_PAGE
        anchors.fill: parent
    }
}
