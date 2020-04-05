#ifndef SWCORE_HPP
#define SWCORE_HPP

#include <QObject>
#include <QTcpServer>
#include <QMap>
#include <QSettings>

#include "client.hpp"
#include "gui/clientitemonform.hpp"

enum MsgType{
    ToPlan = 0,
    ToPopUp = 1,
    ToStatusBar = 3,
    ToStatusBar_PopUp = 4,
    ToPopUp_Plan = 5,
    ToPlan_StatusBar = 6,
    ToAll = 7
};


class swcore : public QObject{
    Q_OBJECT
    Q_PROPERTY(bool status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(quint16 clientCounter READ clientCounter WRITE setClientCounter NOTIFY clientCounterChanged)
    Q_PROPERTY(quint16 port READ port WRITE setPort NOTIFY portChanged)
public:
    swcore(QObject *parent = Q_NULLPTR);
    ~swcore();
    /// geters
    bool status() const;
    quint16 clientCounter() const;
    quint16 port() const;
public slots:
    void slotStartServer(quint8 addr, quint16 _port);
    void slotNewConnection();
    void slotError(QAbstractSocket::SocketError err);
    void slotReadClient();

    void slotClientDiscconected(quint8);
    void slotPauseBroadCast(quint8 id);
    void slotStopBroadCast(quint8 id);
    void slotStartBroadCast(quint8 id,qint64 _min, qint64 _max, quint16 _speed, qint32 _seeq);

    /// seters
    void setStatus(bool status);
    void setClientCounter(quint16 clientCounter);
    void setPort(quint16 port);
    void serverShutDown();
signals:


    void statusChanged(bool status);
    void clientCounterChanged(quint16 clientCounter);
    void portChanged(quint16 port);
    void serverMsg (QString,MsgType);
    void clientConnection(quint8,QString,MsgType);
    void clientDisconnected(quint8);

//    void start(qint64 _min, qint64 _max, quint16 _speed, qint32 _seeq);
    void stop();
    void pause();


private:
    QMap <quint16,client*> SClients;
    quint16 m_maxConnectionsClients;
    QTcpServer *m_server;
    bool m_status;
    quint16 m_clientCounter;
    quint16 m_port;
    bool isLock;
    QSettings *settings;
};

#endif // SWCORE_HPP
