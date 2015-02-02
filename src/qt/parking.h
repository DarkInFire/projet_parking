#ifndef PARKING_H
#define PARKING_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QDebug>
#include "communication.h"

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
