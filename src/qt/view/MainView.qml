import QtQuick 2.4
import QtQuick.Layouts 1.0

Item {
    Image {
        id: rectangle0
        visible: false
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        source: "parking.jpg"
        sourceSize.width: 1280
        sourceSize.height: 720
    }

    Text {
        id: text_const_nbrePlaces
        x: 234
        y: 67
        width: 954
        text: qsTr("Places disponibles")
        wrapMode: Text.WordWrap
        font.pixelSize: 60
    }

    property int places: parking.nbrPlaces
    property bool connected: parking.connected

    property bool place1: parking.place1
    property bool place2: parking.place2
    property bool place3: parking.place3
    property bool place4: parking.place4
    property bool place5: parking.place5
    property bool place6: parking.place6
    property bool place7: parking.place7
    property bool place8: parking.place8
    property bool place9: parking.place9
    property bool place10: parking.place10
    property bool place11: parking.place11
    property bool place12: parking.place12
    property bool place13: parking.place13
    property bool place14: parking.place14
    property bool place15: parking.place15

    onPlacesChanged: {
        text_nbrePlacesDisponibles.text = places;

        place1 = parking.place1;
        place2 = parking.place2;
        place3 = parking.place3;
        place4 = parking.place4;
        place5 = parking.place5;
        place6 = parking.place6;
        place7 = parking.place7;
        place8 = parking.place8;
        place9 = parking.place9;
        place10 = parking.place10;
        place11 = parking.place11;
        place12 = parking.place12;
        place13 = parking.place13;
        place14 = parking.place14;
        place15 = parking.place15;

        if(place1)
            rectangle1.color="#27ae60";
        else
            rectangle1.color="#e74c3c";
        if(place2)
            rectangle2.color="#27ae60";
        else
            rectangle2.color="#e74c3c";
        if(place3)
            rectangle3.color="#27ae60";
        else
            rectangle3.color="#e74c3c";
        if(place4)
            rectangle4.color="#27ae60";
        else
            rectangle4.color="#e74c3c";
        if(place5)
            rectangle5.color="#27ae60";
        else
            rectangle5.color="#e74c3c";
        if(place6)
            rectangle6.color="#27ae60";
        else
            rectangle6.color="#e74c3c";
        if(place7)
            rectangle7.color="#27ae60";
        else
            rectangle7.color="#e74c3c";
        if(place8)
            rectangle8.color="#27ae60";
        else
            rectangle8.color="#e74c3c";
        if(place9)
            rectangle9.color="#27ae60";
        else
            rectangle9.color="#e74c3c";
        if(place10)
            rectangle10.color="#27ae60";
        else
            rectangle10.color="#e74c3c";
        if(place11)
            rectangle11.color="#27ae60";
        else
            rectangle11.color="#e74c3c";
        if(place12)
            rectangle12.color="#27ae60";
        else
            rectangle12.color="#e74c3c";
        if(place13)
            rectangle13.color="#27ae60";
        else
            rectangle13.color="#e74c3c";
        if(place14)
            rectangle14.color="#27ae60";
        else
            rectangle14.color="#e74c3c";
        if(place15)
            rectangle15.color="#27ae60";
        else
            rectangle15.color="#e74c3c";

        console.log(places);
        console.log(place1);
        console.log(place2);
        console.log(place3);
        console.log(place4);
        console.log(place5);
        console.log(place6);
        console.log(place7);
        console.log(place8);
        console.log(place9);
        console.log(place10);
        console.log(place11);
        console.log(place12);
        console.log(place13);
        console.log(place14);
        console.log(place15);
    }

    onConnectedChanged: {
        rectangle1.color="#545454";
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

    Item {
        id: item1
        x: 0
        y: 212
        width: 1280
        height: 500
        visible: true

        Rectangle {
            id: rectangle1
            x: 10
            y: 6
            width: 225
            height: 150
            color: "#f14fff"
        }

        Rectangle {
            id: rectangle2
            x: 266
            y: 6
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle3
            x: 527
            y: 6
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle4
            x: 791
            y: 8
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle5
            x: 1047
            y: 8
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle6
            x: 11
            y: 175
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle7
            x: 267
            y: 175
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle8
            x: 528
            y: 175
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle9
            x: 791
            y: 175
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle10
            x: 1047
            y: 175
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle11
            x: 11
            y: 342
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle12
            x: 267
            y: 342
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle13
            x: 528
            y: 342
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle14
            x: 791
            y: 342
            width: 225
            height: 150
            color: "#ffffff"
        }

        Rectangle {
            id: rectangle15
            x: 1047
            y: 342
            width: 225
            height: 150
            color: "#ffffff"
        }
    }


}
