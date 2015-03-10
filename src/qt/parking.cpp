#include "parking.h"

Parking::Parking(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);

    communication = new Communication(this, QBluetoothAddress("00:13:EF:01:11:8B"));
    connect(communication, SIGNAL(connectedToParking()), this, SLOT(connectedToParking()));
    connect(communication, SIGNAL(connectionFailed(QBluetoothSocket::SocketError)), this, SLOT(connectionFailed(QBluetoothSocket::SocketError)));
    connect(communication, SIGNAL(cmdReceived(quint8,quint8,quint8)), this, SLOT(getCmd(quint8,quint8,quint8)));
}

Parking::~Parking()
{

}

void Parking::connectedToParking()
{
    //Initialisation du parking et synchronisation des données
    askUpdateNbrePlaces();
    sendCmd(cmd_getEtatParking);

    //Mise à jour du tableau des emplacements
    int i;
    for(i=1; i<24; i++)
    {
        sendCmd(cmd_carParkedAtPosition, i);
    }

    qDebug() << "connectedToParking";
}

void Parking::connectionFailed(QBluetoothSocket::SocketError id)
{
    m_timer->start(2500);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(randUpdate()));
    qDebug()<< "connectionFailed: " << id;
}

void Parking::randUpdate()
{
    this->updateNbrePlaces(qrand() % ((42 + 1) - 1) + 1);
    qDebug()<< "randUpdate";
}

void Parking::sendCmd(const quint8 cmd, const quint8 data1, const quint8 data2)
{
    communication->sendCmd(cmd, data1, data2);
}

void Parking::getCmd(const quint8 cmd, const quint8 data1, const quint8 data2)
{
    switch (cmd)
    {
    case msg_nbrPlacesDispo:
        this->updateNbrePlaces(data1);
        break;

    case msg_carParkedAtPosition:
        this->updateEmplacements(data1, data2);
        break;

    case msg_etatParking:
        this->updateEtatParking(data1);
        break;

    default:
        qDebug()<<"Commande invalide";
        break;
    }
}

//Gestion de la variable m_nbrePlaces
void Parking::askUpdateNbrePlaces()
{
    qDebug() << "Parking::updateNbre()";
    communication->sendCmd(cmd_getNbrPlacesDispo);
}

void Parking::updateNbrePlaces(const quint8 nbrePlaces)
{
    this->m_nbrePlaces = nbrePlaces;
    emit nbrePlacesUpdated();
}

quint8 Parking::getNbrePlaces()
{
    return m_nbrePlaces;
}

//Gestion du tableau m_emplacements
void Parking::updateEmplacements(const quint8 position, const quint8 occupied)
{
    if (position == 0 || position > 23 || occupied > 1)
        return;

    this->m_emplacements[position][1] = occupied;
    emit emplacementsUpdated();
}

void Parking::
