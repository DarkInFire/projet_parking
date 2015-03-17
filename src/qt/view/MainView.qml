import QtQuick 2.4
import QtQuick.Layouts 1.0

Item {
    Image {
        id: rectangle1
        anchors.fill: parent
           source: "parking.jpg"
           sourceSize.width: 1280
           sourceSize.height: 720
    }

    Text {
        id: text_const_nbrePlaces
        x: 254
        y: 27
        width: 954
        text: qsTr("Places disponibles")
        wrapMode: Text.WordWrap
        font.pixelSize: 111
    }

    property int places: parking.nbrPlaces

    onPlacesChanged: {
        text_nbrePlacesDisponibles.text = places;
        console.log(places);
        }

    Text {
        id: text_nbrePlacesDisponibles
        x: 8
        y: 13
        text: places
        width: 200
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 148
    }
}
