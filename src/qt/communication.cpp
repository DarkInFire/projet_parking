#include "communication.h"

Communication::Communication(QObject *parent, QBluetoothAddress parkingComAddress) : QObject(parent)
{
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket->connectToService(parkingComAddress, QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
    connect(socket, SIGNAL(connected()), this, SLOT(connectionEtablished()));
}

Communication::~Communication()
{

}

void Communication::connectionEtablished()
{
    emit connectedToParking();
}

void Communication::sendCmd(const int cmd, QByteArray &data)
{
    QByteArray target;
    QDataStream s(&target, QIODevice::ReadWrite);
    s << cmd;
    s << data;
    socket->write(target);
}

void Communication::dataReceived()
{
    if (!socket)
        return;

    if (socket->bytesAvailable() < 1)
        return;

    qint8 command = socket->read(1);

    switch(dataPacket.data[CMD])
    {

    }
}

void Communication::hdlCmd(const int cmd, QByteArray &data)
{

}
