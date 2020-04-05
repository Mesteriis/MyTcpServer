#ifndef STAT_HPP
#define STAT_HPP

#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QDialog>

#include "clickablelabel.hpp"
#include "switchwithid.hpp"


class stat : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QDialog* dialogStat READ dialogStat)
    Q_PROPERTY(quint8 id READ id)
    Q_PROPERTY(QString nameClient READ nameClient)
    Q_PROPERTY(qint16 min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(qint16 max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(quint16 speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(quint16 seeq READ seeq WRITE setSeeq NOTIFY seeqChanged)
    Q_PROPERTY(SwitchWithId* swPause READ swPause)
    Q_PROPERTY(SwitchWithId* swDisconnect READ swDisconnect)
    Q_PROPERTY(QPushButton* pbOk READ pbOk)
    Q_PROPERTY(QPushButton* pbCancel READ pbCancel)
    Q_PROPERTY(QFormLayout* leftLayout READ leftLayout)
    Q_PROPERTY(QFormLayout* rightLayout READ rightLayout)
    Q_PROPERTY(QHBoxLayout* minLay READ minLay)
    Q_PROPERTY(QLabel* idValue READ idValue)
    Q_PROPERTY(QLabel* nameValue READ nameValue)
    Q_PROPERTY(QLabel* minValue READ minValue)
    Q_PROPERTY(QLabel* maxValue READ maxValue)
    Q_PROPERTY(QLabel* speedValue READ speedValue)
    Q_PROPERTY(QLabel* seeqValue READ seeqValue)




public:
    stat(quint8 id, QString name, QWidget *parent = Q_NULLPTR);
    ~stat();

    SwitchWithId *swPause() const;
    SwitchWithId *swDisconnect() const;
    quint8 id() const;
    QDialog *dialogStat() const;

public slots:

    void getStatistics(qint16 min,qint16 max,quint16 speed,quint16 seeq );

signals:
    void minChanged(qint16 min);
    void maxChanged(qint16 max);
    void speedChanged(quint16 speed);
    void seeqChanged(quint16 seeq);
    void RequestStatistics(quint8 id);

private:

    QLabel *idValue() const;
    QLabel *nameValue() const;
    QLabel *minValue() const;
    QLabel *maxValue() const;
    QLabel *speedValue() const;
    QLabel *seeqValue() const;
    void setMin(qint16 min);
    void setMax(qint16 max);
    void setSpeed(quint16 speed);
    void setSeeq(quint16 seeq);
    void setId(quint8 id);
    qint16 min() const;
    qint16 max() const;
    quint16 speed() const;
    quint16 seeq() const;
    QPushButton *pbOk() const;
    QPushButton *pbCancel() const;
    QFormLayout *leftLayout() const;
    QFormLayout *rightLayout() const;
    QHBoxLayout *minLay() const;
    QString nameClient() const;
    qint16 m_min;
    qint16 m_max;
    quint16 m_speed;
    quint16 m_seeq;
    SwitchWithId *m_swPause;
    SwitchWithId *m_swDisconnect;
    QPushButton *m_pbOk;
    QPushButton *m_pbCancel;
    QFormLayout *m_leftLayout;
    QFormLayout *m_rightLayout;
    QHBoxLayout *m_mainLay;
    quint8 m_id;
    QString m_nameClient;
    QLabel *m_labId;
    ClickableLabel *m_labName;
    ClickableLabel *m_labMin;
    ClickableLabel *m_labMax;
    ClickableLabel *m_labSpeed;
    ClickableLabel *m_labSeeq;

    QLabel *m_idValue;
    QLabel *m_nameValue;
    QLabel *m_minValue;
    QLabel *m_maxValue;
    QLabel *m_speedValue;
    QLabel *m_seeqValue;
    QDialog *m_dialogStat;
};

#endif // STAT_HPP
