#include "switchwithid.hpp"

SwitchWithId::SwitchWithId(quint8 id, QString textON, QString textOFF, bool startState, QWidget *parent) : QPushButton(parent){
    setId(id);
    setState(startState);
    setTextON(textON);
    setTextOFF(textOFF);
    (startState) ? setText(textON) : setText(textOFF);

    QObject::connect(this, &QAbstractButton::clicked, this, &SwitchWithId::custClick);
}

quint8 SwitchWithId::id() const{
    return m_id;
}

bool SwitchWithId::state() const{
    return m_state;
}

QString SwitchWithId::textON() const{
    return m_textON;
}

QString SwitchWithId::textOFF() const{
    return m_textOFF;
}

void SwitchWithId::custClick() {
    m_state = (m_state) ? false : true;
    emit click();
}

void SwitchWithId::setId(quint8 id){
    m_id = id;
}

void SwitchWithId::setState(bool state){
    if (m_state == state)
        return;
    m_state = state;
    emit stateChanged(m_state);
}

void SwitchWithId::setTextON(QString textON){
    m_textON = textON;
}

void SwitchWithId::setTextOFF(QString textOFF){
    m_textOFF = textOFF;
}
