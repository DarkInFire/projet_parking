#ifndef PARKING_H
#define PARKING_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QDebug>
#include "communication.h"

//Liste des messages recevables par la tablette
enum msg_tablet
{
    msg_nbrPlacesDispo = 1, //Nombre de places disponibles
};

//Liste des commandes utilisables par l'arduino
enum cmd_arduino
{
    cmd_getNbrPlacesDispo = 1, //Demande du nombre de places disponibles
};

class Parking : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString places READ getNbrePlaces NOTIFY nbrePlacesChanged)

public:
    explicit Parking(QObject *parent = 0);
    ~Parking();

    QString getNbrePlaces();

public slots:
    void updateNbre();
    void connectedToParking();

Q_SIGNALS:
    void nbrePlacesChanged();

private:
    QTimer *m_timer;
    QString m_nbrePlaces;

    Communication *communication;
};

#endif // PARKING_H
