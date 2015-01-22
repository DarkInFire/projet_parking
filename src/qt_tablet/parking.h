#ifndef PARKING_H
#define PARKING_H

#include <QObject>
#include <QTimer>
#include <QBluetoothServiceInfo>
#include <QBluetoothSocket>
#include <QBluetoothServer>
#include <QBluetoothServiceDiscoveryAgent>

static const QString serviceUuid(QStringLiteral("e8e10f95-1a70-4b27-9ccf-02010264e9c9"));

class Parking : public QObject
{
    Q_OBJECT
public:
    explicit Parking(QObject *parent = 0);
    void startDeviceDiscovery();
    ~Parking();

public slots:
    void sendMessage(const QString &message);
    void startClient();

signals:
    void messageReceived(const QString &message);
    void connected(const QString &name);
    void disconnected();
    void started();

private slots:
    void readSocket();
    void connected();

private:
    QBluetoothServer *m_serverInfo;
    QBluetoothServiceInfo m_serviceInfo;
    QBluetoothSocket *socket;
    QBluetoothServiceDiscoveryAgent *discoveryAgent;
    QTimer *m_timer;
};

#endif // PARKING_H
