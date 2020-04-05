#include "clientitemonform.hpp"

clientItemOnForm::clientItemOnForm(quint8 id, QString name, QVBoxLayout *parent)
{
    setId(id);
    m_name = name;
    setParent ((QWidget*)parent);
    br = false;
    m_formLay = new QFormLayout;
    m_formLay->setSpacing(0);
    m_buttonlay = new QHBoxLayout;
    m_buttonlay->setSpacing(0);
    m_pbDisconnect = new SwitchWithId(id,"X","O",true);
    m_pbDisconnect->setStyleSheet("color : red");
    m_pbDisconnect->setMaximumSize(35,35);
    connect(m_pbDisconnect,&SwitchWithId::click,this,&clientItemOnForm::clickPBDisconnect);
    m_pbStopBroadCast = new SwitchWithId(id,"B","S");
    m_pbStopBroadCast->setMaximumSize(35,35);
    m_pbStopBroadCast->setVisible(false);
    connect(m_pbStopBroadCast,&SwitchWithId::click,this,&clientItemOnForm::slotStopBR);
    m_labelNameClient = new ClickableLabel(id);
    m_labelNameClient->setMaximumHeight(30);
    m_labelNameClient->setAlignment(Qt::AlignmentFlag::AlignVCenter);
    m_labelNameClient->setText(name);
    m_labelNameClient->setMinimumWidth(70);
    m_buttonlay->addWidget(m_pbDisconnect);
    m_buttonlay->addWidget(m_pbStopBroadCast);
    m_buttonlay->setAlignment(Qt::AlignmentFlag::AlignRight);
    m_formLay->addRow(m_labelNameClient,m_buttonlay);
    m_formLay->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
}

clientItemOnForm::~clientItemOnForm()
{
    m_formLay->deleteLater();
    m_buttonlay->deleteLater();
    m_pbDisconnect->deleteLater();
    m_pbStopBroadCast->deleteLater();
    m_labelNameClient->deleteLater();
}


void clientItemOnForm::slotSetStatus(qint8 status)
{
    switch (status) {
    case Status::connected:{
        qDebug () << 0;
        /// TODO Animated
        break;
    }
    case Status::pause:{
        qDebug () << 2;
        /// TODO Animated
        break;
    }
    case Status::onAir:{
        qDebug () << 1;
        m_pbStopBroadCast->setVisible(true);
        m_pbDisconnect->setVisible(false);
        m_pbStopBroadCast->setStyleSheet("color : red");
//        m_labelNameClient->setStyleSheet("color : green");
        br = true;
//        m_labelNameClient->setVisible (false);
        pic = ":/pic/broadcastOnAir.gif";
//        pix(pic);
        mo = new QMovie(this);
        mo->setFileName(pic);
        mo->setSpeed(100);
        m_labelNameClient->setMovie (mo);
        m_labelNameClient->setAlignment (Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignVCenter);
        m_labelNameClient->setMaximumSize (QSize(150,35));
        m_labelNameClient->setStyleSheet ("border: 2px solid green;"
                                          "border-radius: 4px;");
        mo->start();
        break;
    }
      case Status::stop:{
          qDebug () << 3;
          m_labelNameClient->setText (m_name);
          m_pbStopBroadCast->setVisible(false);
          m_pbDisconnect->setVisible(true);
          m_pbStopBroadCast->setStyleSheet("color : red");
          m_labelNameClient->setStyleSheet("color : white");
          br = false;
        }
    }
}

void clientItemOnForm::slotStopBR()
{
    slotSetStatus (3);
  emit clickPBStopBroadcast(m_id);

}

void clientItemOnForm::clickPBDisconnect()
{
    emit clickPBDiscon(m_id);

    deleteLater ();
}

QPushButton *clientItemOnForm::pbDisconnect() const
{
    return m_pbDisconnect;
}
SwitchWithId *clientItemOnForm::pbStopBroadCast() const
{
    return m_pbStopBroadCast;
}
ClickableLabel *clientItemOnForm::labelNameClient() const
{
    return m_labelNameClient;
}

bool clientItemOnForm::isBR() const
{
  return br;
}
quint8 clientItemOnForm::id() const
{
  return m_id;
}

QFormLayout *clientItemOnForm::item() const
{
    return m_formLay;
}

void clientItemOnForm::setId(quint8 id)
{
    m_id = id;
}
