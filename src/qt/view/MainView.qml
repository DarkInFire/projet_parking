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
        }
        z: -1
        anchors.fill: parent
    }

    ColumnLayout {
        id: columnLayout1
        anchors.fill: parent
        transformOrigin: Item.Center

        RowLayout {
            id: rowLayout1
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                id: text_nbrePlacesDisponibles
                width: 288
                height: 178
                text: qsTr("42")
                horizontalAlignment: Text.AlignRight
                font.pixelSize: 148
            }

            Text {
                id: text_const_nbrePlaces
                width: 816
                height: 140
                text: qsTr("Places disponibles")
                wrapMode: Text.WordWrap
                font.pixelSize: 100
            }
        }

        Row {
            id: row1
            width: 200
            height: 400
        }

    }


    property string places: parking.places

    onPlacesChanged: {
        text_nbrePlacesDisponibles.text = places;
    }
}
