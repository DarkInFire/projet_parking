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
    msg_nbrPlacesDispo = 1, //Nombre de places disponibles
};

//Liste des commandes utilisables par l'arduino
enum cmd_arduino
{
    cmd_getNbrPlacesDispo = 1, //Demande du nombre de places disponibles
};

class Parking : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 places READ getNbrePlaces NOTIFY nbrePlacesChanged)

public:
    explicit Parking(QObject *parent = 0);
    ~Parking();

    quint8 getNbrePlaces();

public slots:
    void connectedToParking();
    void sendCmd(const quint8 cmd, const quint8 data1 = 0, const quint8 data2 = 0);
    void getCmd(const quint8 cmd, const quint8 data1 = 0, const quint8 data2 = 0);

    void randUpdate();

    void connectionFailed(QBluetoothSocket::SocketError id);

Q_SIGNALS:
    void nbrePlacesChanged();

private:
    QTimer *m_timer;
    quint8 m_nbrePlaces;
    Communication *communication;

    void askUpdateNbrePlaces();
    void updateNbrePlaces(const quint8 nbrePlaces);
};

#endif // PARKING_H
