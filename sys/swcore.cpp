#include "swcore.hpp"

swcore::swcore(QObject *parent)
{
    settings = new QSettings("ShadeInc", "Simple Tcp Graf Server");
    settings->setValue("portServer",6000);
    settings->setValue("maxClient",3);
    settings->sync();

    m_port = settings->value("portServer").toInt();
    m_clientCounter = 0;
    m_status = false;
    m_maxConnectionsClients = settings->value("maxClient").toInt();;
    isLock = false;
    m_server = new QTcpServer(parent);
}

swcore::~swcore()
{
  if (m_server!= Q_NULLPTR){
      m_server->close ();
      m_server->deleteLater ();
    }
    deleteLater ();
}

bool swcore::status() const
{
    return m_status;
}

quint16 swcore::clientCounter() const
{
    return m_clientCounter;
}

quint16 swcore::port() const
{
    return m_port;
}

void swcore::slotStartServer(quint8 addr, quint16 _port)
{   
    setPort(_port);
    connect(m_server,&QTcpServer::newConnection,this,&swcore::slotNewConnection);
    connect(m_server,&QTcpServer::acceptError,this,&swcore::slotError);
    m_server->setMaxPendingConnections(m_maxConnectionsClients);
    if (!m_server->listen((QHostAddress)addr,m_port) && m_status == true){

            emit serverMsg ( QObject::tr("Unable to start the server: %1.").arg(m_server->errorString()),MsgType::ToAll);
        } else {
            setStatus(true);
            emit serverMsg ("Start Server! Lisent on port " + QString::number(m_port) + " ip " + QString::number(m_server->serverAddress().toIPv4Address()),MsgType::ToAll);
        }
}

void swcore::slotNewConnection()
{
    m_clientCounter++;
    isLock = true;
    quint8 id = m_server->socketDescriptor ();
    SClients[id]=new client("Client_" + QString::number(id),id,m_server->nextPendingConnection());
    SClients[id]->setObjectName("Client");
    emit clientConnection(SClients[id]->id(),SClients[id]->name(),MsgType::ToPopUp_Plan);

        connect(SClients[id],    &client::readyRead,     this, &swcore::slotReadClient);
        connect(SClients[id],    &client::disconnected,  this, &swcore::slotClientDiscconected);
        connect(SClients[id],    &client::errorSocket,   this, &swcore::slotError);
}

void swcore::slotError(QAbstractSocket::SocketError err)
{
    QTcpSocket *s  = (QTcpSocket*) sender();
    QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                         "The host was not found." :
                         err == QAbstractSocket::RemoteHostClosedError ?
                         "The remote host is closed." :
                         err == QAbstractSocket::ConnectionRefusedError ?
                         "The connection was refused." :
                         QString(s->errorString().toUtf8()));
    emit serverMsg(strError,MsgType::ToPlan_StatusBar);
}

void swcore::slotReadClient()
{

}

void swcore::slotClientDiscconected(quint8)
{
    QObject *s = sender();
    if (s->objectName() == "Client"){
        client *cl = (client*) s;
        auto scl = SClients.find(cl->id());
        if (scl.value()->socketPoint()->isOpen()){
            emit clientDisconnected(scl.value()->id());

            if (scl.value()->isBroadcasting()){
                if (scl.value()->getWorker()->isRunning()){

                    scl.value()->getWorker()->stop ();
                    scl.value()->getWorker()->deleteLater();
                }
            }
            scl.value()->socketPoint()->close();
            SClients[cl->id()]->deleteLater();
            emit serverMsg("Client disconnected",MsgType::ToAll);
        }
        if (SClients.find(cl->id()) != SClients.end ())SClients.remove (cl->id());
    }
    if (s->objectName() == "clientItemOnForm"){
        clientItemOnForm *clf = (clientItemOnForm*) s;
        auto scl = SClients.find(clf->id());
        if (scl.value()->socketPoint()->isOpen()){
            emit clientDisconnected(scl.value()->id());
            if (scl.value()->isBroadcasting()){
                if (scl.value()->getWorker()->isRunning()){

                    scl.value()->getWorker()->stop();
                    scl.value()->getWorker()->deleteLater();
                }
            }
            scl.value()->socketPoint()->close();
            SClients[clf->id()]->deleteLater();
            emit serverMsg("Client disconnected",MsgType::ToAll);
        }
        if (SClients.find(clf->id()) != SClients.end ())SClients.remove (clf->id());
    }
}

void swcore::slotPauseBroadCast(quint8 id)
{
    SClients[id]->pause ();
}

void swcore::slotStopBroadCast(quint8 id)
{
  SClients[id]->stopBR ();
}

void swcore::slotStartBroadCast(quint8 id, qint64 _min, qint64 _max, quint16 _speed, qint32 _seeq)
{
    SClients[id]->startBR (_min,_max,_speed,_seeq);
}

void swcore::setStatus(bool status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged(m_status);
}

void swcore::setClientCounter(quint16 clientCounter)
{
    if (m_clientCounter == clientCounter)
        return;

    m_clientCounter = clientCounter;
    emit clientCounterChanged(m_clientCounter);
}

void swcore::setPort(quint16 port)
{
    if (m_port == port)
        return;

    m_port = port;
    emit portChanged(m_port);
}

void swcore::serverShutDown()
{
    /// FIXME Подумать
    if (isLock || SClients.isEmpty()) {
        m_server->close();
        setStatus(false);
    } else {
    for (auto i : SClients){
        if (i->isBroadcasting()){

        } else {
            i->socketPoint()->close(); /// TODO заменить на сигнал
            SClients.remove(i->id());  /// TODO заменить на сигнал
            if (SClients.isEmpty()) isLock = true;
        }
    }
    }
    if (isLock) {
        m_server->close();
        setStatus(false);
    }

}
