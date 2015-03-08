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
    connect(this, SIGNAL(dataInBuffer()), this, SLOT(dataReceived()));
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
        buffer = socket->read(4);
    else
        buffer.append(socket->read(3));

    if (!checkToken(buffer[1]))
        return;

    emit cmdReceived(buffer[0], buffer[2], buffer[3]);

    if (socket->bytesAvailable() > 1)
        emit dataInBuffer();
}

bool Communication::checkToken(const quint8 token)
{
    return (token == 18) ? true : false;
}
