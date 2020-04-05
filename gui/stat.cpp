#include "stat.hpp"

stat::stat( quint8 id, QString name, QWidget *parent)
{
    setId(id);
    m_nameClient=name;
    m_dialogStat = new QDialog(parent);
    m_dialogStat->setMinimumWidth(400);
    emit RequestStatistics(id);

    m_leftLayout = new QFormLayout;

    m_labId = new ClickableLabel(id);
    m_labId->setText("ID : ");
    m_idValue = new QLabel;
    m_idValue->setNum(m_id);
    m_leftLayout->addRow(m_labId,m_idValue);
    m_labMin = new ClickableLabel(id);
    m_labMin->setText("Min : ");
    m_minValue = new QLabel;
    m_minValue->setNum(m_min);
    m_leftLayout->addRow(m_labMin,m_minValue);
    m_labMax = new ClickableLabel(id);
    m_labMax->setText("Max : ");
    m_maxValue = new QLabel;
    m_maxValue->setNum(m_max);
    m_leftLayout->addRow(m_labMax,m_maxValue);
    m_swPause = new SwitchWithId(id,"Continue","Pause",false);
    m_pbOk = new QPushButton;
    connect(m_pbOk,&QPushButton::clicked,m_dialogStat,&QDialog::accept);
    m_pbOk->setText("OK");
    m_leftLayout->addRow(m_pbOk,m_swPause);

    m_rightLayout = new QFormLayout;
    m_labName = new ClickableLabel(id);
    m_labName->setText("Client name : ");
    m_nameValue = new QLabel;
    m_nameValue->setText(m_nameClient);
    m_rightLayout->addRow(m_labName,m_nameValue);
    m_labSpeed = new ClickableLabel(id);
    m_labSpeed->setText("Speed : ");
    m_speedValue = new QLabel;
    m_speedValue->setNum(m_speed);
    m_rightLayout->addRow(m_labSpeed,m_speedValue);
    m_labSeeq = new ClickableLabel(id);
    m_labSeeq->setText("Seeq : ");
    m_seeqValue = new QLabel;
    m_seeqValue->setNum(m_seeq);
    m_rightLayout->addRow(m_labSeeq,m_seeqValue);
    m_swDisconnect = new SwitchWithId(id,"disconnect","",true);
    m_pbCancel = new QPushButton;
    m_pbCancel->setText("Cancel");
    connect(m_pbCancel,&QPushButton::clicked,m_dialogStat,&QDialog::reject);
    m_rightLayout->addRow(m_swDisconnect,m_pbCancel);
    m_mainLay = new QHBoxLayout;
    m_mainLay->addLayout(m_leftLayout);
    m_mainLay->addLayout(m_rightLayout);
    m_dialogStat->setLayout(m_mainLay);
    int minSize = 110;
    m_pbCancel->setMinimumWidth(minSize);
    m_swDisconnect->setMinimumWidth(minSize);
    m_swPause->setMinimumWidth(minSize);
    m_pbOk->setMinimumWidth(minSize);
    m_dialogStat->exec();
}

stat::~stat()
{
    delete m_dialogStat;
    deleteLater();
}

void stat::getStatistics(qint16 min, qint16 max, quint16 speed, quint16 seeq)
{
    setMin(min);
    setMax(max);
    setSpeed(speed);
    setSeeq(seeq);

    m_minValue->setNum(min);
    m_maxValue->setNum(max);
    m_speedValue->setNum(speed);
    m_seeqValue->setNum(seeq);

    m_dialogStat->exec();
}

QLabel *stat::idValue() const
{
    return m_idValue;
}

QLabel *stat::nameValue() const
{
    return m_nameValue;
}

QLabel *stat::minValue() const
{
    return m_minValue;
}

QLabel *stat::maxValue() const
{
    return m_maxValue;
}

QLabel *stat::speedValue() const
{
    return m_speedValue;
}

QLabel *stat::seeqValue() const
{
    return m_seeqValue;
}

qint16 stat::min() const
{
    return m_min;
}

qint16 stat::max() const
{
    return m_max;
}

quint16 stat::speed() const
{
    return m_speed;
}

quint16 stat::seeq() const
{
    return m_seeq;
}

SwitchWithId *stat::swPause() const
{
    return m_swPause;
}

SwitchWithId *stat::swDisconnect() const
{
    return m_swDisconnect;
}

QPushButton *stat::pbOk() const
{
    return m_pbOk;
}

QPushButton *stat::pbCancel() const
{
    return m_pbCancel;
}

QFormLayout *stat::leftLayout() const
{
    return m_leftLayout;
}

QFormLayout *stat::rightLayout() const
{
    return m_rightLayout;
}

QHBoxLayout *stat::minLay() const
{
    return m_mainLay;
}

quint8 stat::id() const
{
    return m_id;
}

QString stat::nameClient() const
{
    return m_nameClient;
}






QDialog *stat::dialogStat() const
{
    return m_dialogStat;
}

void stat::setMin(qint16 min)
{
    if (m_min == min)
        return;

    m_min = min;
    emit minChanged(m_min);
}

void stat::setMax(qint16 max)
{
    if (m_max == max)
        return;

    m_max = max;
    emit maxChanged(m_max);
}

void stat::setSpeed(quint16 speed)
{
    if (m_speed == speed)
        return;

    m_speed = speed;
    emit speedChanged(m_speed);
}

void stat::setSeeq(quint16 seeq)
{
    if (m_seeq == seeq)
        return;

    m_seeq = seeq;
    emit seeqChanged(m_seeq);
}

void stat::setId(quint8 id)
{
    m_id = id;
}


