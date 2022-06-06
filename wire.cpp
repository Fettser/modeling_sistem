#include "wire.h"
#include <QGraphicsSceneMouseEvent>

Wire::Wire(QObject *parent) :
    QObject(parent) {
    setObjectName("wire");
}

Wire::Wire(QObject *parent, QPointF start, QPointF end) : QObject(parent) {
   setFirstPoint(start);
   setSecondPoint(end);
   setObjectName("wire");
}

Wire::~Wire() {

}

QPointF Wire::firstPoint() const
{
    return m_firstPoint;
}

void Wire::setFirstPoint(const QPointF point)
{
    if (m_firstPoint == point)
        return;

    m_firstPoint = point;
    emit firstPointChanged();
}

QPointF Wire::secondPoint() const
{
    return m_secondPoint;
}

void Wire::setSecondPoint(const QPointF point)
{
    if (m_secondPoint == point)
        return;

    m_secondPoint = point;
    emit secondPointChanged();
}

void Wire::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        emit onSelectElement(this);
    }
}
