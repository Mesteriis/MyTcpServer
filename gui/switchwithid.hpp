#ifndef SWITCHWITHID_HPP
#define SWITCHWITHID_HPP

#include <QObject>
#include <QPushButton>

class SwitchWithId : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(quint8 id READ id WRITE setId)
    Q_PROPERTY(bool state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString textON READ textON WRITE setTextON)
    Q_PROPERTY(QString textOFF READ textOFF WRITE setTextOFF)
public:
    SwitchWithId(quint8 id,
                 QString textON,
                 QString textOFF,
                 bool startState = false,
                 QWidget *parent = Q_NULLPTR);

    quint8 id() const;
    bool state() const;
    QString textON() const;
    QString textOFF() const;
signals:
//    void click(quint8);
    void click();
    void stateChanged(bool state);
public slots:
    void custClick(); // (void)
    void setId(quint8 id);
    void setState(bool state);
    void setTextON(QString textON);
    void setTextOFF(QString textOFF);
private:
    quint8 m_id;
    bool m_state;
    QString m_textON;
    QString m_textOFF;
};

#endif // SWITCHWITHID_HPP
