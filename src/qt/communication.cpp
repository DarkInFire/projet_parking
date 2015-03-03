#include "communication.h"

Communication::Communication(QObject *parent, QBluetoothAddress parkingComAddress) : QObject(parent)
{
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket->connectToService(parkingComAddress, QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
    connect(socket, SIGNAL(connected()), this, SLOT(connectionEtablished()));

    stream = new QDataStream(socket);

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
    qDebug()<< "Communication::dataReceived";
    if (!socket)
    {
        qDebug()<< "Communication::socketERREUR";
        return;
    }

    qDebug()<< "Communication::socketOK";

    if (socket->bytesAvailable() < 1)
    {
        qDebug()<< "No DATA available";
        return;
    }

    //Vérification des données

    qDebug()<<socket->bytesAvailable();
    QByteArray buffer;
    buffer.resize(4);
    buffer = socket->read(4);
    quint8 cmd = buffer[0];
    quint8 token = buffer[1];
    quint8 msg1 = buffer[2];
    quint8 msg2 = buffer[3];
    qDebug()<< "cmd at 0: " << cmd;
    qDebug()<< "tok at 1: " << token;
    qDebug()<< "ms1 at 2: " << msg1;
    qDebug()<< "ms2 at 3: " << msg2;
    qDebug()<< "buffer.data: \"" << buffer.data()<< "\"";

    emit cmdReceived(cmd, msg1, msg2);
}

