#include "parking.h"

Parking::Parking(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);

    communication = new Communication(this, QBluetoothAddress("00:13:EF:00:06:4F"));
    connect(communication, SIGNAL(connectedToParking()), this, SLOT(connectedToParking()));
}

Parking::~Parking()
{

}

void Parking::connectedToParking()
{
    m_timer->start(1000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateNbre()));

}

void updateNbre()
{

}

QString Parking::getNbrePlaces()
{
    return m_nbrePlaces;
}
