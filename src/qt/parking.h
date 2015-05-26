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
    Q_PROPERTY(bool connected READ connectedOrNot NOTIFY connectedChange)
    Q_PROPERTY(bool place1 READ place1 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place2 READ place2 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place3 READ place3 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place4 READ place4 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place5 READ place5 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place6 READ place6 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place7 READ place7 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place8 READ place8 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place9 READ place9 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place10 READ place10 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place11 READ place11 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place12 READ place12 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place13 READ place13 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place14 READ place14 NOTIFY nbrePlacesChanged)
    Q_PROPERTY(bool place15 READ place15 NOTIFY nbrePlacesChanged)

public:
    explicit Parking(QObject *parent = 0);
    ~Parking();

    Q_INVOKABLE quint8 nbrPlaces();
    Q_INVOKABLE bool connected();
    Q_INVOKABLE bool place1();
	Q_INVOKABLE bool place2();
	Q_INVOKABLE bool place3();
	Q_INVOKABLE bool place4();
	Q_INVOKABLE bool place5();
	Q_INVOKABLE bool place6();
	Q_INVOKABLE bool place7();
	Q_INVOKABLE bool place8();
	Q_INVOKABLE bool place9();
	Q_INVOKABLE bool place10();
	Q_INVOKABLE bool place11();
	Q_INVOKABLE bool place12();
	Q_INVOKABLE bool place13();
	Q_INVOKABLE bool place14();
	Q_INVOKABLE bool place15();

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
    void connectedChange();

private:
    QTimer *m_timer;
    Communication *communication;

    bool connectedOrNot;

    bool m_emplacements[15];
    quint8 m_nbrePlaces;
    quint8 m_etatParking;

    bool checkToken(const quint8 token);

    void updateNbrePlaces(const quint8 nbrePlaces);
    void updateEmplacements(const quint8 position, const quint8 occupied);
    void updateEtatParking(const quint8 etatParking);

    quint8 calcNbrePlaces();
};

#endif // PARKING_H
