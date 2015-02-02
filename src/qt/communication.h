#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QBluetoothSocket>

//Définie les valeurs du service Bluetooth
static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));

//Liste des messages recevables par la tablette
enum msg_tablet
{
    nbrPlacesDisponibles = 1,
};

//Liste des commandes utilisables par l'arduino
enum cmd_arduino
{
    getNbrePlacesDisponibles = 1,
};

//Définition du paquet
enum PACKET_DETAILS{
    CMD = 0,
    BYTE_1,
    BYTE_2,
    BYTE_3,
};

struct
{
    quint8 data[BUFFER_LIMIT];
    quint8 curLoc;
} dataPacket;

/*
 * Classe communication
 * Gère les entrés/sorties de la tablette
 */

class Communication : public QObject
{
    Q_OBJECT
public:
    explicit Communication(QObject *parent = 0, QBluetoothAddress parkingComAddress);
    ~Communication();

signals:

public slots:
    //Envoie/Réception de données
    void sendCmd(const int cmd, QByteArray &data);
    void hdlCmd (const int cmd, QByteArray &data);

    //Bluetooth slots
    void connectionEtablished();
    void dataReceived();

signals:
    void connectedToParking();

private:

    QBluetoothSocket *socket;
    QBluetoothAddress parkingComAdress;
};

#endif // COMMUNICATION_H
