#include "resistor.h"
#include <QPainter>
#include <QCursor>

Resistor::Resistor(QObject *parent) :
    Element(parent) {

}
Resistor::~Resistor() {

}

int Resistor::resistance() const
{
    return m_resistance;
}

void Resistor::setResistance(const int resistance)
{
    if (m_resistance == resistance)
        return;

    m_resistance = resistance;
    emit resistanceChanged();
}

void Resistor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::black);
    QFont font = painter->font();
    font.setPixelSize(16);
    if(this->isSelected()) {
        painter->drawRect(-48, -25, 97, 50);
    }
    painter->setFont(font);
    painter->drawPixmap(-48,-25,QPixmap(":elements/img/resistor.png"));
    painter->drawText(this->boundingRect(), Qt::AlignCenter, QString::number(m_resistance) + " Om");
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
