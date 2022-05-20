#include "capacitor.h"
#include <QPainter>
#include <QCursor>

Capacitor::Capacitor(QObject *parent) :
    Element(parent) {

}
Capacitor::~Capacitor() {

}

int Capacitor::capacity() const
{
    return m_capacity;
}

void Capacitor::setCapacity(const int capacity)
{
    if (m_capacity == capacity)
        return;

    m_capacity= capacity;
    emit capacityChanged();
}

void Capacitor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
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
    painter->drawLine(-48, 0, -5, 0);
    painter->drawLine(5, 0, 49, 0);
    painter->drawLine(-5, 20, -5, -20);
    painter->drawLine(5, 20, 5, -20);
    painter->drawText(this->boundingRect(), Qt::AlignLeft | Qt::AlignTop, QString::number(m_capacity) + " pF");
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
