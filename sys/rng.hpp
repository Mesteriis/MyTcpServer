#ifndef RNG_HPP
#define RNG_HPP

#include <QObject>
#include <QThread>
#include <QDebug>

class rng : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(quint16 max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(quint16 speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(quint16 seeq READ seeq WRITE setSeeq NOTIFY seeqChanged)
    Q_PROPERTY(bool isPause READ isPause WRITE setIsPause NOTIFY isPauseChanged)
    Q_PROPERTY(bool isWork READ isWork WRITE setIsWork NOTIFY isWorkChanged)
    Q_PROPERTY(bool finishid READ isFinishid WRITE setFinishid )
public:
    rng( QObject *parent = Q_NULLPTR);
    ~rng();
    bool isPause() const;
    bool isWork() const;
    bool isFinishid() const;
    bool firstStart;
    qint64 min() const;
    qint64 max() const;
    quint16 speed() const;
    qint32 seeq() const;


public slots:
    bool setParams (qint64 _min, qint64 _max, quint16 _speed, qint32 _seeq);

    void setIsPause(bool isPause);
    void setIsWork(bool isWork);
    void setFinishid(bool finishid);
    void run();
    void stop()
    {
        setIsWork (false);
        setFinishid (true);
    }
    void pause()
    {
        setIsPause (true);
    }

signals:
    void minChanged(qint64 min);
    void maxChanged(qint64 max);
    void speedChanged(quint16 speed);
    void seeqChanged(qint32 seeq);
    void isPauseChanged(bool isPause);
    void isWorkChanged(bool isWork);
    void resultTik (qint64,qint64);

    void finished();


private:

    void setMin(qint64 min);
    void setMax(qint64 max);
    void setSpeed(quint16 speed);
    void setSeeq(qint32 seeq);




    qint64 m_min;
    qint64 m_max;
    quint16 m_speed;
    qint32 m_seeq;
    bool m_isPause;
    bool m_isWork;
    bool m_finishid;
};

#endif // RNG_HPP
