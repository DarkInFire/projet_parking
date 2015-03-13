#ifndef PARKING_H
#define PARKING_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QDebug>
#include "communication.h"

//Liste des messages recevables par la tablette
enum msg_tablet
{
    msg_nbrPlacesDispo = 1, //Nombre de places disponibles en data1
    msg_carParkedAtPosition, //Si une voiture est garée à l'emplacement data1, data2 = 1
    msg_etatParking, //Renvoie l'état du parking
    msg_ready,
};

//Liste des commandes utilisables par l'arduino
enum cmd_arduino
{
    cmd_getNbrPlacesDispo = 1, //Demande du nombre de places disponibles
    cmd_carParkedAtPosition, //Demande si une voiture est gérée à l'empalcement data1
    cmd_getEtatParking, //Demande l'état du parking
    cmd_invalidData,
};

class Parking : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 nbrPlaces READ nbrPlaces NOTIFY nbrePlacesChanged)

public:
    explicit Parking(QObject *parent = 0);
    ~Parking();

    Q_INVOKABLE quint8 nbrPlaces();

public slots:
    //Bluetooth
    void connectedToParking();
    void connectionFailed(QBluetoothSocket::SocketError id);

    //Envoie/réception
    void sendCmd(const quint8 cmd, const quint8 data1 = 0, const quint8 data2 = 0);
    void getCmd(const quint8 cmd, const quint8 data1 = 0, const quint8 data2 = 0);

    //Simulation
    void randUpdate();

    //Commandes
    void askUpdateNbrePlaces();

Q_SIGNALS:
    void emplacementsUpdated();
    void nbrePlacesChanged();

private:
    QTimer *m_timer;
    Communication *communication;

    quint8 m_emplacements[2];
    quint8 m_nbrePlaces;
    quint8 m_etatParking;

    bool checkToken(const quint8 token);

    void updateNbrePlaces(const quint8 nbrePlaces);
    void updateEmplacements(const quint8 position, const quint8 occupied);
    void updateEtatParking(const quint8 etatParking);
};

#endif // PARKING_H
