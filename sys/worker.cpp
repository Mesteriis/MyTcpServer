#include "worker.hpp"



worker::worker(QObject *parent)
{
    setParent (parent);
    setObjectName ("worker_");
    m_pause = false;
    m_isFinished = false;
    m_isRunning = false;
    stream = new QThread(this);
    stream->setObjectName ("Stream User_" + parent->objectName ());
    m_generator = new rng;
    stream->setObjectName ("Generator User_" + parent->objectName ());
    m_generator->moveToThread (stream);
    connect (this, &worker::startBR,          m_generator, &rng::run);
    connect (this, &worker::setParamGen,       m_generator, &rng::setParams,   Qt::ConnectionType::DirectConnection);
    //        connect (this, &worker::maxChanged,       m_generator, &rng::setMax,   Qt::ConnectionType::DirectConnection);
    //        connect (this, &worker::speedChanged,     m_generator, &rng::setSpeed, Qt::ConnectionType::DirectConnection);
    //        connect (this, &worker::seeqChanged,      m_generator, &rng::setSeeq,  Qt::ConnectionType::DirectConnection);
    //        connect (this, &worker::pauseBR,          m_generator, &rng::pause,    Qt::ConnectionType::DirectConnection);
    //        connect (this, &worker::stopBR,           m_generator, &rng::stop,     Qt::ConnectionType::DirectConnection);
    connect (m_generator,&rng::resultTik,this,&worker::sendPair);
    stream->start ();
}

worker::~worker()
{
    m_generator->setIsWork (false);
    m_generator->setIsPause (false);
    QThread::msleep (m_speed + 10);
    m_generator->deleteLater ();
    stream->terminate ();
    stream->deleteLater ();
    QThread::msleep (m_speed + 10);
//    qDebug () << "Delete: " << stream->objectName () << stream;
//    qDebug () << "Delete: " << m_generator->objectName () << m_generator;
    m_generator = Q_NULLPTR;
    stream = Q_NULLPTR;
    deleteLater ();
}

bool worker::isFinished() const
{
    return m_isFinished;
}

bool worker::isRunning() const
{
    return m_isRunning;
}

rng *worker::generator() const
{
    return m_generator;
}

bool worker::isPause() const
{
    return m_pause;
}

