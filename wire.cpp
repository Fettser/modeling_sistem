#include "wire.h"
#include <QGraphicsSceneMouseEvent>

Wire::Wire(QObject *parent) :
    QObject(parent) {

}
Wire::~Wire() {

}

void Wire::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        emit onSelectElement(this);
    }
}
