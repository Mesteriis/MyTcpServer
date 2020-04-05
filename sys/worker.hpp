#ifndef WORKER_HPP
#define WORKER_HPP

#include <QObject>
#include <QThread>

#include "rng.hpp"

class worker : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(bool isBroadcasting READ isBroadcasting WRITE setIsBroadcasting NOTIFY isBroadcastingChanged)
//    Q_PROPERTY(bool isFinished READ isFinished WRITE setIsFinished NOTIFY isFinishedChanged)
//    Q_PROPERTY(bool isRunning READ isRunning WRITE setIsRunning NOTIFY isRunningChanged)
    Q_PROPERTY(rng* generator READ generator)
//    Q_PROPERTY(quint16 min READ min WRITE setMin NOTIFY minChanged)
//    Q_PROPERTY(quint16 max READ max WRITE setMax NOTIFY maxChanged)
//    Q_PROPERTY(quint16 speed READ speed WRITE setSpeed NOTIFY speedChanged)
//    Q_PROPERTY(quint16 seeq READ seeq WRITE setSeeq NOTIFY seeqChanged)
//    Q_PROPERTY(bool pause READ isPause WRITE setPause NOTIFY pauseChanged)





public:
    worker(QObject *parent = Q_NULLPTR);
    ~worker();


    bool isFinished() const;
    bool isRunning() const;
    bool isPause() const;

public slots:
    void run(qint64 _min, qint64 _max, quint16 _speed, qint32 _seeq)
    {
        qDebug () << objectName () << "run";
        m_speed = _speed;
        bool isReady = false;
        if (m_generator->isWork()){
            m_generator->setIsWork (false);
            isReady = m_generator->setParams (_min,_max,_speed,_seeq);
            if (isReady) emit startBR ();
        }
        if (m_generator->isPause()){
            m_generator->setIsPause (false);
            m_generator->setIsWork (false);
            isReady = m_generator->setParams (_min,_max,_speed,_seeq);
            if (isReady) emit startBR ();
        }
        if (m_generator->isFinishid ()){
            isReady = m_generator->setParams (_min,_max,_speed,_seeq);
            if (isReady) emit startBR ();
        }
        if (m_generator->firstStart){
            isReady = m_generator->setParams (_min,_max,_speed,_seeq);
            if (isReady) {
                m_isFinished = false;
                m_isRunning = true;
                emit startBR ();
            }
        }
    }
    void stop()
    {
        m_generator->setIsPause (false);
        m_generator->setIsWork (false);
        m_isFinished = true;
    }
    void pause()
    {
        m_pause = true;
        m_isRunning = true;
        m_generator->setIsPause (true);
    }
signals:

    void startBR();
    void sendPair(qint64,qint64);
    void setParamGen(qint64 _min, qint64 _max, quint16 _speed, qint32 _seeq);

    void minChanged(quint16 min);
    void maxChanged(quint16 max);
    void speedChanged(quint16 speed);
    void seeqChanged(quint16 seeq);
    void pauseChanged(bool pause);

private:
    quint16 m_speed;
    rng* generator() const;

//    bool m_isBroadcasting;
    bool m_isFinished;
    bool m_isRunning;
    rng *m_generator;
    QThread *stream;
    bool m_pause;
};

#endif // WORKER_HPP
