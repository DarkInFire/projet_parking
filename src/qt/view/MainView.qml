import QtQuick 2.4
import QtQuick.Layouts 1.0

Item {
    width: 1280
    height: 720
    Rectangle {
        id: rectangle1
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#56e466"
            }

            GradientStop {
                position: 1
                color: "#a3c9a8"
            }

            GradientStop {
                position: 2
                color: "#a354a8"
            }
        }
        z: -1
        anchors.fill: parent
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

    Text {
        id: text_nbrePlacesDisponibles
        x: 8
        y: 13
        text: qsTr("20")
        width: 200
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 148
    }

    property string places: parking.places

    onPlacesChanged: {
        text_nbrePlacesDisponibles.text = places;
        }
}
