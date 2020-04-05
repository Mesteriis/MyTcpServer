#include "rng.hpp"


rng::rng(QObject *parent)
{
    setParent (parent);
    setObjectName ("rng_");
    setParams (0,100,500,321);
    m_isPause = false;
    m_isWork = false;
    m_finishid = false;
    firstStart = true;
}

rng::~rng()
{
    //        qDebug () << "Delete: " + objectName ();
    setIsWork (false);
    setIsPause (false);
    QThread::msleep (m_speed + 10);
    deleteLater ();
}


bool rng::setParams(qint64 _min, qint64 _max, quint16 _speed, qint32 _seeq)
{
    m_min = _min;
    m_max = _max;
    m_speed = _speed;
    m_seeq = _seeq;
    m_isPause = false;
    m_isWork = false;
    m_finishid = false;
  return true;
}

qint64 rng::min() const
{
    return m_min;
}

qint64 rng::max() const
{
    return m_max;
}

quint16 rng::speed() const
{
    return m_speed;
}

qint32 rng::seeq() const
{
    return m_seeq;
}



bool rng::isPause() const
{
    return m_isPause;
}

bool rng::isWork() const
{
    return m_isWork;
}

bool rng::isFinishid() const
{
    return m_finishid;
}



void rng::setMin(qint64 min)
{
    if (m_min == min)
        return;

    m_min = min;
    emit minChanged(m_min);
}

void rng::setMax(qint64 max)
{
    if (m_max == max)
        return;

    m_max = max;
    emit maxChanged(m_max);
}

void rng::setSpeed(quint16 speed)
{
    if (m_speed == speed)
        return;

    m_speed = speed;
    emit speedChanged(m_speed);
}

void rng::setSeeq(qint32 seeq)
{
    if (m_seeq == seeq)
        return;

    m_seeq = seeq;
    emit seeqChanged(m_seeq);
}

void rng::setIsPause(bool isPause)
{
    if (m_isPause == isPause)
        return;

    m_isPause = isPause;
    emit isPauseChanged(m_isPause);
}

void rng::setIsWork(bool isWork)
{
    if (m_isWork == isWork)
        return;

    m_isWork = isWork;
    emit isWorkChanged(m_isWork);
}

void rng::setFinishid(bool finishid)
{
  if (m_finishid == finishid)
    return;

  m_finishid = finishid;
  if (m_finishid) emit finished();
}

void rng::run()
{
    firstStart = false;
    qDebug () << objectName ();
    setIsWork (true);
    qsrand(seeq());
    qint64 abscissaValue = 0;
    while (isWork ()) {
            qint64 ordinateValue = ((qrand() % ((max() + 1) - min()) + min()));
            abscissaValue++;
            QThread::msleep(speed());
            qDebug () << this->objectName () << abscissaValue << " " << ordinateValue;
            emit resultTik (abscissaValue,ordinateValue);
            if (isPause ()){
                    while (isPause()) {
                            QThread::msleep(500);
                        }
                }
            //                      if (abscissaValue == 10) break;
        }
    emit finished ();
}


