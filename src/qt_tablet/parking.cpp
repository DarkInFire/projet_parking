#include "parking.h"

Parking::Parking(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
}

Parking::~Parking()
{

}

void Parking::startClient()
{
    //! [Searching for the service]
    discoveryAgent = new QBluetoothServiceDiscoveryAgent(QBluetoothAddress());

    connect(discoveryAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SLOT(addService(QBluetoothServiceInfo)));

    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(done()));

    connect(discoveryAgent, SIGNAL(error(QBluetoothServiceDiscoveryAgent::Error)),
            this, SLOT(serviceScanError(QBluetoothServiceDiscoveryAgent::Error)));

    discoveryAgent->setUuidFilter(QBluetoothUuid(serviceUuid));

    discoveryAgent->start(QBluetoothServiceDiscoveryAgent::FullDiscovery);
    //! [Searching for the service]

    emit started();
}

void Parking::sendMessage(const QString &message)
{
    QByteArray text = message.toUtf8() + '\n';
    socket->write(text);
}

void Parking::readSocket()
{
    if (!socket)
        return;

    while (socket->canReadLine()) {
        QByteArray line = socket->readLine();
        emit messageReceived(QString::fromUtf8(line.constData(), line.length()));
    }
}
