#ifndef PARKING_H
#define PARKING_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QDebug>
#include <qbluetoothserver.h>
#include <qbluetoothserviceinfo.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothservicediscoveryagent.h>

static const QString serviceUuid(QStringLiteral("e8e10f95-1a70-4b27-9ccf-02010264e9c9"));

class Parking : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString places READ nbrePlaces NOTIFY messageChanged)

public:
    explicit Parking(QObject *parent = 0);
    ~Parking();
    int randNbre(int low, int high);
    QString nbrePlaces();

public slots:
    void updateNbre();
    void startClient();
    void setMessage(const QString &message);
    void serviceScanError(QBluetoothServiceDiscoveryAgent::Error);
    void done();
    void addService(const QBluetoothServiceInfo &);
    void serverDisconnected();

Q_SIGNALS:
    void messageChanged();

private:
    QTimer *m_timer;
    QString m_nbrePlaces;
    QBluetoothServer *m_serverInfo;
    QBluetoothServiceInfo m_serviceInfo;
    QBluetoothSocket *socket;
    QBluetoothServiceDiscoveryAgent *discoveryAgent;
    bool m_serviceFound;

};

#endif // PARKING_H
