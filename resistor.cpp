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
        painter->drawRect(-50, -25, 100, 50);
    }
    painter->setFont(font);
    QPen pen = QPen();
    pen.setWidth(4);
    painter->setPen(pen);
    painter->drawRect(-35, -20, 70, 40);
    painter->drawLine(-48, 0, -35, 0);
    painter->drawLine(35, 0, 49, 0);
    painter->drawText(this->boundingRect(), Qt::AlignCenter, QString::number(m_resistance) + " Om");
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
