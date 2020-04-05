#include "client.hpp"

client::client(QString name, quint8 id, QTcpSocket *socket, QObject *parent)
{
    setParent (parent);
    setSocketPoint(socket);
    setName(name);
    setObjectName (name + "_" + id);
    setId(id);
    connect(m_socketPoint, &QTcpSocket::disconnected, this, &client::slotDisconnected);
    connect(m_socketPoint, &QIODevice::readyRead,     this, &client::readyRead);
    connect(m_socketPoint, static_cast<void(QTcpSocket::*) (QAbstractSocket::SocketError)>  (&QTcpSocket::error),
            this,          static_cast<void(client::*)     (QAbstractSocket::SocketError)>  (&client::errorSocket));
    m_worker = new worker(this);
    connect (this,&client::start , m_worker,&worker::run );
    connect (m_worker,&worker::sendPair, this,&client::sendPair);


}

client::~client()
{
    if (socketPoint ()->isOpen ()){
            socketPoint ()->close ();
        }
    if (m_worker!= Q_NULLPTR){
            m_worker->deleteLater ();
        }
        deleteLater ();
}

QString client::name() const
{
    return m_name;
}

bool client::isAlive() const
{
    return m_isAlive;
}

quint8 client::id() const
{
    return m_id;
}

QTcpSocket *client::socketPoint() const
{
    return m_socketPoint;
}

bool client::isBroadcasting() const
{
    return m_isBroadcasting;
}

void client::setName(QString name)
{
    m_name = name;
}

void client::setIsAlive(bool isAlive)
{
    if (m_isAlive == isAlive)
        return;

    m_isAlive = isAlive;
    emit isAliveChanged(m_isAlive);
}

void client::setId(quint8 id)
{
    if (m_id == id)
        return;
    m_id = id;
}

void client::setIsBroadcasting(bool isBroadcasting)
{
    if (m_isBroadcasting == isBroadcasting)
        return;

    m_isBroadcasting = isBroadcasting;
    emit isBroadcastingChanged(m_isBroadcasting);
}

void client::sendPair(qint64 x, qint64 y)
{
    QString str = "2%" + QString::number (x) + "#" + QString::number (y) + "\n";
    if (m_socketPoint->isOpen ()){
            m_socketPoint->write(str.toUtf8 ());
        }
}

void client::startBR(qint64 _min, qint64 _max, quint16 _speed, qint32 _seeq)
{
    qDebug () << objectName () << "startBR";
    emit start (_min,_max,_speed,_seeq);


}

void client::stopBR()
{

    m_worker->stop ();
}

void client::slotDisconnected()
{
    emit disconnected(m_id);
}

worker *client::getWorker() const
{
    return m_worker;
}

void client::setSocketPoint(QTcpSocket *socketPoint)
{
    m_socketPoint = socketPoint;
}
