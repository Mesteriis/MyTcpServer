#ifndef CLIENTITEMONFORM_HPP
#define CLIENTITEMONFORM_HPP

#include <QWidget>
#include "clickablelabel.hpp"
#include "switchwithid.hpp"
#include "stat.hpp"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QMovie>


enum Status{
    connected = 0,
    onAir = 1,
    pause = 2,
    stop = 3
};

class clientItemOnForm : public QWidget
{
    Q_OBJECT


    Q_PROPERTY(QFormLayout* item READ item )
    Q_PROPERTY(QPushButton* pbDisconnect READ pbDisconnect )
    Q_PROPERTY(SwitchWithId* pbStopBroadCast READ pbStopBroadCast)
    Q_PROPERTY(ClickableLabel* labelNameClient READ labelNameClient)
    Q_PROPERTY(quint8 id READ id WRITE setId)


public:
    clientItemOnForm(quint8 id, QString name, QVBoxLayout *parent = Q_NULLPTR);
    ~clientItemOnForm();
    QFormLayout *item() const;
    quint8 id() const;

    bool isBR() const;

public slots:
    void slotSetStatus(qint8 status);
    void slotStopBR();
    void clickPBDisconnect();

signals:

   void clickPBDiscon(quint8 id);
   void clickPBStopBroadcast(quint8 id);

private:
    void setId(quint8 id);
    QPushButton* pbDisconnect() const;
    SwitchWithId* pbStopBroadCast() const;
    ClickableLabel* labelNameClient() const;

    QHBoxLayout *m_buttonlay;
    QFormLayout* m_formLay;
    SwitchWithId *m_pbStopBroadCast;
    SwitchWithId* m_pbDisconnect;
    ClickableLabel  *m_labelNameClient;
    quint8 m_id;
    QWidget *m_wdj;
    bool br;
    QString m_name;

    QString pic ;
    QPixmap pix;
    QMovie *mo;
};

#endif // CLIENTITEMONFORM_HPP
