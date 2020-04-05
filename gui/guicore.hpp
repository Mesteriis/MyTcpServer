#ifndef GUICORE_HPP
#define GUICORE_HPP

#include <QMainWindow>
#include <QMessageBox>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QComboBox>

#include "sys/swcore.hpp"
#include "clientitemonform.hpp"
#include "stat.hpp"
#include "popup.hpp"
#include <QSpinBox>



QT_BEGIN_NAMESPACE
namespace Ui { class guicore; }
QT_END_NAMESPACE

class guicore : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(bool serverStatus READ serverStatus WRITE setServerStatus NOTIFY serverStatusChanged)


public:
    guicore(QWidget *parent = nullptr);
    ~guicore();

    bool serverStatus() const;


public slots:
    void setServerStatus(bool serverStatus);
    void serverMsg (QString msg, MsgType type);

    void slotAddNewClientOnForm(quint8 id, QString name, MsgType type = MsgType::ToAll);
    void slotDeleteClientOfForm(quint8 id);
    void slotStopBroadCast(quint8 id);


signals:
    void serverStatusChanged(bool serverStatus);
    void serverStart (quint8,quint16);
    void serverShutDown();

    void disclientsOnServer();
    void startBroadCast(quint8 id,qint64 _min, qint64 _max, quint16 _speed, qint32 _seeq);
    void stopBC(quint8 id);
    void pauseBroadCast(quint8 id);


private slots:
    void on_pushButtonStartServer_clicked();

    void on_pushButtonStopServer_clicked();

    void on_pushButtonStartBroadCast_clicked();

private:
    QMap <quint8,clientItemOnForm*> SClientsOnForm;
    Ui::guicore *ui;
    swcore *swc;
    bool m_serverStatus;
    PopUp *PUp;
};
#endif // GUICORE_HPP
