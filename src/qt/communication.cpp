#include "communication.h"

Communication::Communication(QObject *parent, QBluetoothAddress parkingComAddress) : QObject(parent)
{
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket->connectToService(parkingComAddress, QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
    connect(socket, SIGNAL(connected()), this, SLOT(connectionEtablished()));
    connect(socket, SIGNAL(error(QBluetoothSocket::SocketError)), this, SIGNAL(connectionFailed(QBluetoothSocket::SocketError)));

    stream = new QDataStream(socket);

    connectionInitialized = false;

    qDebug() << "Communication::Communication";
}

Communication::~Communication()
{
    socket->close();
}

void Communication::connectionEtablished()
{
    token = 18;
    emit connectedToParking();
    connect(socket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    qDebug() << "Communication::Communication";
}

void Communication::sendCmd(const quint8 cmd, const quint8 data1, const quint8 data2)
{
    QByteArray dataTransmit;
    dataTransmit.resize(4);
    dataTransmit[0] = cmd;
    dataTransmit[1] = token;
    dataTransmit[2] = data1;
    dataTransmit[3] = data2;
    stream->writeRawData(dataTransmit, 4);

    qDebug() << "send cmd";
}

void Communication::dataReceived()
{
    /*Lire une commande
     *
     * Vérifier si l'arduino est connecté
     *
     * Vérifier si des données sont dispo
     *
     * Lire 1 octet de donnée
     *
     * Si l'octet lu est égal à 255 (valeur de start)
     *  Lire les 4 prochains octets (cmd, crc, msg1, msg2)
     * SINON
     *  Lire les 3 prochains octets, la valeur lue précedemment est la commande (crc, msg1, msg2)
     *
     * Vérifier que le token est 18
     *
     * Envoyer le signal cmdReceived
     */
    if (!socket)
    {
        qDebug()<< "Communication::socketERREUR";
        return;
    }

    if (socket->bytesAvailable() < 1)
    {
        qDebug()<< "No DATA available";
        return;
    }

    QByteArray buffer = socket->read(1);

    if (buffer[0] == 255)
    {
        buffer = socket->read(4);
    }
    else
    {
        buffer.append(socket->read(3));
    }

    emit cmdReceived(buffer[1], msg1, msg2);

    qDebug()<< "start: " << start;
    qDebug()<< "cmd at 0: " << cmd;
    qDebug()<< "tok at 1: " << token;
    qDebug()<< "ms1 at 2: " << msg1;
    qDebug()<< "ms2 at 3: " << msg2;

    socket->readAll();
}
