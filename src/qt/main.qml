import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Hello World")
    visible: true
    height: 1280
    width: 720

    Text {
        id: nbrePlacesDisponibles
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        x: parent.width / 2 -200
        y: 100

        font.pixelSize: 150
        property string places: parking.places
        onPlacesChanged: {
            nbrePlacesDisponibles.text = places;
        }
    }
}
