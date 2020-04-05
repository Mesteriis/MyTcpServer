#include "clickablelabel.hpp"

ClickableLabel::ClickableLabel(quint8 id, QWidget* parent)
    : QLabel(parent){
    setId(id);
}

ClickableLabel::~ClickableLabel(){

}

quint8 ClickableLabel::id() const
{
    return m_id;
}

void ClickableLabel::setId(quint8 id)
{
    m_id = id;
}

void ClickableLabel::mousePressEvent(QMouseEvent* ){
    emit clicked();
}
