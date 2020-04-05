#ifndef CLICKABLELABEL_HPP
#define CLICKABLELABEL_HPP

#include <QLabel>

class ClickableLabel : public QLabel{
    Q_OBJECT
    Q_PROPERTY(quint8 id READ id WRITE setId)
    quint8 m_id;

public:
    explicit ClickableLabel(quint8 id,QWidget* parent = Q_NULLPTR);
~ClickableLabel();
quint8 id() const;

public slots:
void setId(quint8 id);

signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent*);


};

#endif // CLICKABLELABEL_HPP
