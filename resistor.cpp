#include "resistor.h"
#include <QPainter>
#include <QCursor>

Resistor::Resistor(QObject *parent, QString resistance) :
    Element(parent) {
    setObjectName("resistor");
    setResistance(resistance);
}
Resistor::~Resistor() {

}

QString Resistor::resistance() const
{
    return m_resistance;
}

void Resistor::setResistance(const QString resistance)
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
    painter->drawText(this->boundingRect(), Qt::AlignCenter, m_resistance);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
