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

void Communication::sendCmd(const quint8 cmd, const quint8 &data1, const quint8 &data2)
{
    QByteArray dataTransmit;
    dataTransmit[0] = cmd;
    dataTransmit[1] = token;
    dataTransmit[2] = data1;
    dataTransmit[3] = data2;
    stream->writeRawData(dataTransmit, 4);

    qDebug() << "send cmd with data";
}

void Communication::sendCmd(const quint8 cmd)
{
    QByteArray dataTransmit;
    dataTransmit.resize(4);
    dataTransmit[0] = cmd;
    dataTransmit[1] = token;
    dataTransmit[2] = 127;
    dataTransmit[3] = 127;
    stream->writeRawData(dataTransmit, 4);

    qDebug() << "send cmd without data";
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

   /* if (socket->bytesAvailable() < 3)
    {
        qDebug()<< "Less than 3 bytes available";
        return;
    }*/

    char temp[4];

    qDebug()<<temp;

}
