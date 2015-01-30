#include "parking.h"

Parking::Parking(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);

    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
        socket->connectToService(QBluetoothAddress("00:13:EF:00:06:4F"), QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);
        connect(socket, SIGNAL(connected()), this, SLOT(connectionEtablished()));

    qDebug() << "Parking initialisé";
}

Parking::~Parking()
{

    qDebug() << "Destructeur";
}

void Parking::connectionEtablished()
{
    m_timer->start(1000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateNbre()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(cmdRecv()));
}

void Parking::cmdRecv()
{
    if (!socket)
        return;

    while (socket->canReadLine()) {
        QByteArray line = socket->readLine();
        m_nbrePlaces = line;
        Q_EMIT messageChanged();

    }
}

void Parking::updateNbre()
{
    QByteArray target;
    QDataStream s(&target, QIODevice::ReadWrite);
    const char valeur = 'a';
    s << valeur;
    socket->write(target);
    //Q_EMIT messageChanged();
    qDebug() << "Envoie de A sur l'arduino";
}

void Parking::setMessage(const QString &Message)
{
    m_nbrePlaces = Message;
    Q_EMIT messageChanged();
    qDebug() << "setMessage";
}

QString Parking::nbrePlaces()
{
    return m_nbrePlaces;
}

