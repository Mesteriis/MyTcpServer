#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QObject>
#include <QTcpSocket>
#include "worker.hpp"

//QTcpSocket QTcpSocket;

class client : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(bool isAlive READ isAlive WRITE setIsAlive NOTIFY isAliveChanged)
    Q_PROPERTY(quint8 id READ id WRITE setId )
    Q_PROPERTY(QTcpSocket *socketPoint READ socketPoint)
    Q_PROPERTY(bool isBroadcasting READ isBroadcasting WRITE setIsBroadcasting NOTIFY isBroadcastingChanged)
public:
    client(QString name,quint8 id,QTcpSocket *socket ,QObject *parent = Q_NULLPTR);
    ~client();





    bool isAlive() const;
    quint8 id() const;
    bool isBroadcasting() const;
    QTcpSocket *socketPoint() const;
    worker *getWorker() const;

public slots:
    void setName(QString name);
    void setIsAlive(bool isAlive);
    void setId(quint8 id);
    void setIsBroadcasting(bool isBroadcasting);
    void sendPair(qint64 x,qint64 y);
    void startBR(qint64 _min, qint64 _max, quint16 _speed, qint32 _seeq);
    void stopBR();
    void slotDisconnected();
    QString name() const;
signals:
    void isAliveChanged(bool isAlive);
    void disconnected(quint8);

    void isBroadcastingChanged(bool isBroadcasting);
    void readyRead();
    void errorSocket(QAbstractSocket::SocketError);
    /// worker
    void start(qint64 _min, qint64 _max, quint16 _speed, qint32 _seeq);
    void stop();
    void pause();

private:


    void setSocketPoint(QTcpSocket *socketPoint);


    /// vars
    QString m_name;
    bool m_isAlive;
    quint8 m_id;
    QTcpSocket *m_socketPoint;
    bool m_isBroadcasting;
    worker *m_worker;
};

#endif // CLIENT_HPP
