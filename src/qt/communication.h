#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QBluetoothSocket>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <sstream>

//Définie les valeurs du service Bluetooth
static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));


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
    void sendCmd(const quint8 cmd, const quint8 &data);
    void sendCmd(const quint8 cmd);

    //Slots Bluetooth
    void connectionEtablished();
    void dataReceived();

signals:
    void connectedToParking();

private:
    QBluetoothSocket *socket;
    QBluetoothAddress parkingComAdress;
    QDataStream *stream;
    quint8 token;
    bool correctPacket;
    bool connectionInitialized;
};

#endif // COMMUNICATION_H
