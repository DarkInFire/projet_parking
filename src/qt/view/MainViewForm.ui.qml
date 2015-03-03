import QtQuick 2.4

Item {
    Text {
        id: text_nbrePlacesDisponibles
        x: 85
        y: 34
        width: 288
        height: 178
        text: qsTr("42")
        horizontalAlignment: Text.AlignRight
        font.pixelSize: 148
    }

    Text {
        id: text_const_nbrePlaces
        x: 410
        y: 58
        width: 816
        height: 140
        text: qsTr("Places disponibles")
        wrapMode: Text.WordWrap
        font.pixelSize: 100
    }
}

