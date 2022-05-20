#include "inductor.h"
#include <QPainter>
#include <QCursor>

Inductor::Inductor(QObject *parent) :
    Element(parent) {

}
Inductor::~Inductor() {

}

int Inductor::inductance() const
{
    return m_inductance;
}

void Inductor::setInductance(const int inductance)
{
    if (m_inductance == inductance)
        return;

    m_inductance= inductance;
    emit inductanceChanged();
}

void Inductor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
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
    painter->drawLine(-48, 0, -40, 0);
    painter->drawLine(40, 0, 49, 0);
    painter->drawArc(-40, -10, 20, 20, 0, 2880);
    painter->drawArc(-20, -10, 20, 20, 0, 2880);
    painter->drawArc(0, -10, 20, 20, 0, 2880);
    painter->drawArc(20, -10, 20, 20, 0, 2880);
    painter->drawText(this->boundingRect(), Qt::AlignLeft | Qt::AlignBottom, QString::number(m_inductance) + " pF");
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
