import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Hello World")
    visible: true
    height: 1280
    width: 720

    Component.onCompleted: pageLoader.source = "view/MainView.qml"

        Loader {
            id: pageLoader
            anchors.fill: parent
        }
}
