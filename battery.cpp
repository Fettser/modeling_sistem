#include "battery.h"
#include <QPainter>
#include <QCursor>
#include <QPixmap>

Battery::Battery(QObject *parent) :
    Element(parent)
{

}
Battery::~Battery() {

}

int Battery::resistance() const
{
    return m_resistance;
}

void Battery::setResistance(const int resistance)
{
    if (m_resistance == resistance)
        return;

    m_resistance = resistance;
    emit resistanceChanged();
}

int Battery::voltage() const
{
    return m_voltage;
}

void Battery::setVoltage(const int voltage)
{
    if (m_voltage == voltage)
        return;

    m_voltage = voltage;
    emit voltageChanged();
}

void Battery::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(Qt::black);
    QFont font = painter->font();
    font.setPixelSize(16);
    if(this->isSelected()) {
        painter->drawRect(-48, -25, 97, 50);
    }
    painter->setFont(font);
    painter->drawPixmap(-48, -25, QPixmap(":elements/img/battery.png"));
    painter->drawText(this->boundingRect(), Qt::AlignLeft | Qt::AlignTop, QString::number(m_voltage)+"V");
    painter->drawText(this->boundingRect(), Qt::AlignRight | Qt::AlignTop, QString::number(m_resistance) + "Om");
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


