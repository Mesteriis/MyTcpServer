#include "guicore.hpp"

#include "ui_guicore.h"



guicore::guicore(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::guicore)
{
    ui->setupUi(this);
    ui->pushButtonStopServer->setDisabled(true);
    ui->pushButtonDisconnectAll->setDisabled(true);
    ui->pushButtonStartBroadCast->setDisabled(true);

    PUp = new PopUp();

    swc = new swcore(this);
    connect(swc,&swcore::statusChanged,this,&guicore::setServerStatus);
    connect(swc,&swcore::serverMsg,this,&guicore::serverMsg);
    connect(this,&guicore::serverStart,swc,&swcore::slotStartServer);
    connect(this,&guicore::serverShutDown,swc,&swcore::serverShutDown);
    connect(swc,&swcore::clientConnection,this,&guicore::slotAddNewClientOnForm);
    connect(swc,&swcore::clientDisconnected,this,&guicore::slotDeleteClientOfForm);
    connect(this,&guicore::stopBC,swc,&swcore::slotStopBroadCast);
    connect (this,&guicore::startBroadCast, swc,&swcore::slotStartBroadCast );

    ui->pushButtonStartServer->click ();

}

guicore::~guicore()
{
    delete ui;
}

bool guicore::serverStatus() const
{
    return m_serverStatus;
}

void guicore::setServerStatus(bool serverStatus)
{
    if (m_serverStatus == serverStatus)
        return;
    (m_serverStatus) ? ui->labelStatusValue->setText("OFFLINE") : ui->labelStatusValue->setText("ONLINE");
    (m_serverStatus) ? ui->labelStatusValue->setStyleSheet("color : red") : ui->labelStatusValue->setStyleSheet("color : green") ;
    (m_serverStatus) ? ui->pushButtonStartServer->setDisabled(false) : ui->pushButtonStartServer->setDisabled(true);
    (m_serverStatus) ? ui->pushButtonStopServer->setDisabled(true) : ui->pushButtonStopServer->setDisabled(false);
    m_serverStatus = serverStatus;
}

void guicore::serverMsg(QString msg, MsgType type)
{
    switch (type) {
    case ToPlan:{
        ui->textEditLogs->append(msg);
        break;
    }
    case ToPopUp:{
        PUp->setPopupText(msg);
        PUp->show();
        break;
    }
    case ToStatusBar:{
        ui->statusbar->showMessage(msg,3);
        break;
    }
    case ToStatusBar_PopUp:{
        ui->statusbar->showMessage(msg,3);
        PUp->setPopupText(msg);
        PUp->show();

        break;
    }
    case ToPopUp_Plan:{
        PUp->setPopupText(msg);
        PUp->show();
        ui->textEditLogs->append(msg);
        break;
    }
    case ToPlan_StatusBar:{
        ui->textEditLogs->append(msg);
        ui->statusbar->showMessage(msg,3);
        break;
    }
    case MsgType::ToAll:{
        ui->statusbar->showMessage(msg,3);
        ui->textEditLogs->append(msg);
        PUp->setPopupText(msg);
        PUp->show();
        break;
    }

    }
}

void guicore::slotAddNewClientOnForm(quint8 id, QString name,MsgType type)
{
    serverMsg("New connected detected! ID: " + QString::number(id) + ", Name: " + name +".",type);
    SClientsOnForm[id] = new clientItemOnForm(id,name);
    SClientsOnForm[id]->setObjectName("clientItemOnForm");
    SClientsOnForm[id]->slotSetStatus(0);
    ui->verticalLayoutClientList->addLayout(SClientsOnForm[id]->item());
    ui->pushButtonStartBroadCast->setDisabled (false);

    /// TODO connect to SClient
    connect(SClientsOnForm[id],&clientItemOnForm::clickPBDiscon,swc,&swcore::slotClientDiscconected);
//    connect(SClientsOnForm[id],&clientItemOnForm::clickPBDiscon,swc,&swcore::slotClientDiscconected);

//    connect(SClientsOnForm[id],&clientItemOnForm::clickPBDisconnect,this,&guicore::disclientsOnServer);
    connect(SClientsOnForm[id],&clientItemOnForm::clickPBStopBroadcast,this,&guicore::slotStopBroadCast);

}

void guicore::slotDeleteClientOfForm(quint8 id)
{

    SClientsOnForm.remove (id);
}

void guicore::slotStopBroadCast(quint8 id)
{
  int x=0;
  emit stopBC (id);
  for (auto i : SClientsOnForm) {
      if (i->isBR ()) x++;
    }
  if (x < SClientsOnForm.size ()) ui->pushButtonStartBroadCast->setDisabled (false);
}


void guicore::on_pushButtonStartServer_clicked()
{
    QDialog * dialogServSettings = new QDialog;
    QLineEdit *lePortServ        = new QLineEdit(dialogServSettings);
    QFormLayout *layout          = new QFormLayout(dialogServSettings);
    QComboBox * cbLisentAddr     = new QComboBox(dialogServSettings);
    cbLisentAddr->insertItem(4,"Any");           // The dual stack any-address.
    cbLisentAddr->insertItem(0,"Null");          // The null address object.
    cbLisentAddr->insertItem(1,"Broadcast");     // The IPv4 broadcast address.
    cbLisentAddr->insertItem(2,"LocalHost");     // The IPv4 localhost address.
    cbLisentAddr->insertItem(3,"LocalHostIPv6"); // The IPv6 localhost address.
    cbLisentAddr->insertItem(5,"AnyIPv6");       // The IPv6 any-address.
    cbLisentAddr->insertItem(6,"AnyIPv4");       // The IPv4 any-address.
    cbLisentAddr->setToolTip("Select lisent type server");

    QDialogButtonBox *btn_box = new QDialogButtonBox(dialogServSettings);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel );

    connect (btn_box, &QDialogButtonBox::accepted, dialogServSettings, &QDialog::accept);
    connect (btn_box, &QDialogButtonBox::rejected, dialogServSettings, &QDialog::reject);

    layout->addRow(new QLabel(tr("Port Server")), lePortServ);
    layout->addRow(new QLabel(tr("Lisent Address")),cbLisentAddr);
    layout->addWidget(btn_box);
    dialogServSettings->setLayout(layout);

    lePortServ->setText("6000");
    dialogServSettings->setModal(true);
    emit serverStart(cbLisentAddr->currentIndex(),6000);
//    if (dialogServSettings->exec() == QDialog::Accepted){
//        emit serverStart(cbLisentAddr->currentIndex(),6000);
//    }
    delete dialogServSettings;
}

void guicore::on_pushButtonStopServer_clicked()
{
    emit serverShutDown();
}

void guicore::on_pushButtonStartBroadCast_clicked()
{

  QDialog *dialogBroadCast = new QDialog;
  QComboBox *cbClientsName = new QComboBox(dialogBroadCast);
  cbClientsName->setMinimumWidth(160);
  QSpinBox *sbOrdMin = new QSpinBox(dialogBroadCast);
  sbOrdMin->setMinimumWidth(150);
  sbOrdMin->setRange(0,80);
  sbOrdMin->setValue(0);
  QSpinBox *sbOrdMax = new QSpinBox(dialogBroadCast);
  sbOrdMax->setMinimumWidth(150);
  sbOrdMax->setRange(20,100);
  sbOrdMax->setValue(100);
  QSpinBox *sbInterval = new QSpinBox(dialogBroadCast);
  sbInterval->setMinimumWidth(150);
  sbInterval->setRange(20,1000);
  sbInterval->setValue(500);
  QLineEdit *seed = new QLineEdit(dialogBroadCast);
  seed->setMinimumWidth(150);
  seed->setText("567");

  for (auto i : SClientsOnForm) {
      if (!i->isBR ()){
          cbClientsName->addItem(QString::number (i->id ()));
        }
    }

  QDialogButtonBox *btn_box = new QDialogButtonBox(dialogBroadCast);
  btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel );

  connect (btn_box, &QDialogButtonBox::accepted, dialogBroadCast, &QDialog::accept);
  connect (btn_box, &QDialogButtonBox::rejected, dialogBroadCast, &QDialog::reject);

  QFormLayout *layout = new QFormLayout(dialogBroadCast);
  layout->addRow(new QLabel(tr("ID")), cbClientsName);

  dialogBroadCast->setMinimumWidth(300);

  layout->addRow(new QLabel(tr("ordinate min")), sbOrdMin);
  layout->addRow(new QLabel(tr("ordinate max")), sbOrdMax);
  layout->addRow(new QLabel(tr("Interval")), sbInterval);
  layout->addRow(new QLabel(tr("seed")), seed);
  layout->addWidget(btn_box);
  dialogBroadCast->setLayout(layout);
  if (dialogBroadCast->exec() == QDialog::Accepted){
      int _id = cbClientsName->currentText ().toInt ();
    emit startBroadCast(_id,sbOrdMin->value (),sbOrdMax->value (),sbInterval->value (),seed->text ().toInt ());
    SClientsOnForm[_id]->slotSetStatus(1);
    int freeCL = 0;
    for (auto i : SClientsOnForm) {
         if (!i->isBR ()) freeCL++;
      }
    if (freeCL!=0){
        ui->pushButtonStartBroadCast->setDisabled(false);
    } else {
        ui->pushButtonStartBroadCast->setDisabled(true);
    }
  } else {
    QMessageBox::information(0, "Information", "Clients is not connectid");
  }
  dialogBroadCast->deleteLater();
}
