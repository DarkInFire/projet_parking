#include "parking.h"

Parking::Parking(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);
   connect(m_timer, SIGNAL(timeout()), this, SLOT(updateNbre()));
    //m_timer->start(1000);
    qDebug() << "Initialisé";
    startClient();
}

Parking::~Parking()
{

    qDebug() << "Destructeur";
}

void Parking::updateNbre()
{
    QString nbre = QString::number(randNbre(0,100));
    m_nbrePlaces = nbre;
    Q_EMIT messageChanged();
    qDebug() << "updateNbre";
}


void Parking::setMessage(const QString &Message)
{
    m_nbrePlaces = Message;
    Q_EMIT messageChanged();
    qDebug() << "setMessage";
}

int Parking::randNbre(int low, int high)
{
    qDebug() << "random";
    return qrand() % ((high + 1) - low) + low;
}

QString Parking::nbrePlaces()
{
    qDebug() << "nbrePlaces";
    return m_nbrePlaces;
}

void Parking::startClient()
{
    discoveryAgent = new QBluetoothServiceDiscoveryAgent(QBluetoothAddress());
    qDebug() << "new discorevy agent";
    connect(discoveryAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
            this, SLOT(addService(QBluetoothServiceInfo)));
    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(done()));
    connect(discoveryAgent, SIGNAL(error(QBluetoothServiceDiscoveryAgent::Error)),
            this, SLOT(serviceScanError(QBluetoothServiceDiscoveryAgent::Error)));
    qDebug() << "connect";
    discoveryAgent->setRemoteAddress(QBluetoothAddress("0073E031352F"));
    qDebug() << "remote";
    discoveryAgent->start(QBluetoothServiceDiscoveryAgent::FullDiscovery);
    qDebug() << "start";
    //! [Searching for the service]
    setMessage(QStringLiteral("Starting server discovery."));
}

void Parking::done()
{
    qDebug() << "Service scan done";
    if (!m_serviceFound)
        setMessage("not found");
}

void Parking::addService(const QBluetoothServiceInfo &service)
{
    setMessage("Service found. Setting parameters...");
    //! [Connecting the socket]
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket->connectToService(service);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(socket, SIGNAL(connected()), this, SLOT(serverConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(serverDisconnected()));
    //! [Connecting the socket]
    m_serviceFound = true;
}

void Parking::serviceScanError(QBluetoothServiceDiscoveryAgent::Error error)
{
    setMessage(QStringLiteral("Scanning error") + error);
}

void Parking::serverDisconnected()
{
    setMessage("Server Disconnected");
    m_timer->stop();
}
