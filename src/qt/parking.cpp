#include "parking.h"
#include "stdlib.h"

Parking::Parking(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);

    communication = new Communication(this, QBluetoothAddress("00:13:EF:01:13:21"));
    connect(communication, SIGNAL(connectedToParking()), this, SLOT(connectedToParking()));
    connect(communication, SIGNAL(connectionFailed(QBluetoothSocket::SocketError)), this, SLOT(connectionFailed(QBluetoothSocket::SocketError)));
    connect(communication, SIGNAL(cmdReceived(quint8,quint8,quint8)), this, SLOT(getCmd(quint8,quint8,quint8)));

    for(int i=0; i<15; i++)
    {
         this->m_emplacements[i] = false;
    }

    this->m_nbrePlaces = calcNbrePlaces();

    connectedOrNot = false;
}

Parking::~Parking()
{

}

void Parking::connectedToParking()
{
    //Initialisation du parking et synchronisation des données
    askUpdateNbrePlaces();
    sendCmd(cmd_getEtatParking);

    connectedOrNot = true;

    emit connectedChange();


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
    qDebug()<< "RAND UPDATE";

    for(int i=0; i<15; i++)
    {

        this->m_emplacements[i] = rand() % 2 == 1;
        qDebug() << m_emplacements[i];
    }

    updateNbrePlaces(calcNbrePlaces());

    qDebug()<< "randUpdate nbr_places: ";
    emit nbrePlacesChanged();
}

void Parking::sendCmd(const quint8 cmd, const quint8 data1, const quint8 data2)
{
    communication->sendCmd(cmd, data1, data2);
}

void Parking::getCmd(const quint8 cmd, const quint8 data1, const quint8 data2)
{
    qDebug() << "cmdreceived" << cmd;
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

    qDebug() << this->m_nbrePlaces;

    emit nbrePlacesChanged();
}

quint8 Parking::nbrPlaces()
{
    qDebug() << "nbrPlaces";
    return this->m_nbrePlaces;
}

bool Parking::place1()
{
    return this->m_emplacements[0];
}

bool Parking::place2()
{
    return this->m_emplacements[1];
}

bool Parking::place3()
{
    return this->m_emplacements[2];
}

bool Parking::place4()
{
    return this->m_emplacements[3];
}

bool Parking::place5()
{
    return this->m_emplacements[4];
}

bool Parking::place6()
{
    return this->m_emplacements[5];
}

bool Parking::place7()
{
    return this->m_emplacements[6];
}

bool Parking::place8()
{
    return this->m_emplacements[7];
}

bool Parking::place9()
{
    return this->m_emplacements[8];
}

bool Parking::place10()
{
    return this->m_emplacements[9];
}

bool Parking::place11()
{
    return this->m_emplacements[10];
}

bool Parking::place12()
{
    return this->m_emplacements[11];
}

bool Parking::place13()
{
    return this->m_emplacements[12];
}

bool Parking::place14()
{
    return this->m_emplacements[13];
}

bool Parking::place15()
{
    return this->m_emplacements[14];
}

//Gestion du tableau m_emplacements
void Parking::updateEmplacements(const quint8 position, const quint8 occupied)
{
    this->m_emplacements[position] = occupied;
    updateNbrePlaces(calcNbrePlaces());
    emit emplacementsUpdated();
}

void Parking::updateEtatParking(const quint8 etatParking)
{
    this->m_etatParking = etatParking;
}

quint8 Parking::calcNbrePlaces()
{
    int nbr_places = 0;
    for(int i=0; i<15; i++)
    {
        if (this->m_emplacements[i])
        {
            nbr_places++;
        }
        qDebug() << this->m_emplacements[i];
    }

    qDebug() << "NOMBRE DE PLACES CALCNBRPLACES :";
    qDebug() << nbr_places;
    return nbr_places;

}
