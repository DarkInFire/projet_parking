#include "communication.h"

Communication::Communication(QObject *parent, QBluetoothAddress parkingComAddress) : QObject(parent)
{
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket->connectToService(parkingComAddress, QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
    connect(socket, SIGNAL(connected()), this, SLOT(connectionEtablished()));
}

Communication::~Communication()
{
    socket->close();
}

void Communication::connectionEtablished()
{
    emit connectedToParking();
}

void Communication::sendCmd(const int cmd, QByteArray &data)
{
    QByteArray command;
    QDataStream s(&command, QIODevice::ReadWrite);
    s << cmd;
    socket->write(command);

    socket->write(data);
}

void Communication::dataReceived()
{
    if (!socket)
        return;

    if (socket->bytesAvailable() < 1)
        return;



}

void Communication::getCmd(const int cmd, QByteArray &data)
{

}
