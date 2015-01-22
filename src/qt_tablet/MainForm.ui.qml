import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

 Item {
    width: 640
    height: 480

    RowLayout {
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent

        Text {
            id: nbrePlacesDisponibles
            text: qsTr("35")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 78
        }
    }
}
