#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QBluetoothSocket>

//Définie les valeurs du service Bluetooth
static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));

const int BUFFER_LIMIT = 4; //Limite du buffer

//Liste des messages recevables par la tablette
enum msg_tablet
{
    nbrPlacesDisponibles = 0 //Nombre de places disponibles
};

//Liste des commandes utilisables par l'arduino
enum cmd_arduino
{
    getNbrePlacesDisponibles = 0 //Demande du nombre de places disponibles
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
    explicit Communication(QObject *parent = 0, QBluetoothAddress parkingComAddress = QBluetoothAddress("00:13:EF:01:11:8B"));
    ~Communication();

signals:

public slots:
    //Envoie/Réception de données
    void sendCmd(const int cmd, QByteArray &data);
    void getCmd (const int cmd, QByteArray &data);

    //Slots Bluetooth
    void connectionEtablished();
    void dataReceived();

signals:
    void connectedToParking();

private:
    QBluetoothSocket *socket;
    QBluetoothAddress parkingComAdress;
};

#endif // COMMUNICATION_H
