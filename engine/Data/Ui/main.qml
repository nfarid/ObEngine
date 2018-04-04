import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2

ApplicationWindow {
    id: applicationWindow
    objectName: "applicationWindow"
    visible: true
    width: Screen.desktopAvailableHeight / 2
    height: Screen.desktopAvailableHeight / 2
    title: qsTr("ÖbEngine Dev")
    flags: Qt.FramelessWindowHint | Qt.Window

    Loader {
        id: loader
        objectName: "loader"
        anchors.fill: parent
        source: load_source
    }
}