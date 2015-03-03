import QtQuick 2.4

MainViewForm {
    width: 1280
    height: 720

    property string places: parking.places
    
    onPlacesChanged: {
        MainViewForm.text_nbrePlacesDisponibles = places;
    }
}

