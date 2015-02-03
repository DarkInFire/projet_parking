#include "parking.h"

Parking::Parking(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);

    communication = new Communication(this, QBluetoothAddress("00:13:EF:01:11:8B"));
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

void Parking::updateNbre()
{

}

QString Parking::getNbrePlaces()
{
    return m_nbrePlaces;
}
