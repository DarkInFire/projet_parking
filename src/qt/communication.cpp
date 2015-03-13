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

void Communication::invalidData()
{
    socket->readAll();
    sendCmd(4);
}

void Communication::dataReceived()
{
    qDebug()<< "dataReceived";
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

    readData(socket->read(1));
}

void Communication::readData(const QByteArray firstByte)
{
    qDebug() << "readData";

    QByteArray buffer = firstByte;

    if (buffer[0] == 255)
        buffer = socket->read(4);
    else
        buffer.append(socket->read(3));

    quint8 cmd = buffer[0];
    quint8 token = buffer[1];
    quint8 msg1 = buffer[2];
    quint8 msg2 = buffer[3];

    qDebug() << "buffer[0]: " << cmd << "buffer[1]: " << token << "buffer[2]: " << msg1 << "buffer[3]: " << msg2;

    if (!checkToken(token))
    {
        qDebug() << "bad token";
        invalidData();
        return;
    }

    emit cmdReceived(cmd, msg1, msg2);
}

void Communication::checkCommectionInitialize(const QByteArray data)
{
    quint8 byte1 = data[0];
    quint8 byte2 = data[1];

    if (byte1 == 255 && byte2 == 255)
    {
        qDebug() << "Connection initialisé";
        this->connectionInitialized = true;
        sendCmd(255);
    }

    socket->readAll();
}

bool Communication::checkToken(const quint8 token)
{
    return (token == 18) ? true : false;
}
