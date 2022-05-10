#include "element.h"
#include "math.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

Element::Element(QObject *parent) : QObject(parent), QGraphicsItem() {
    setIsSelected(false);
    connect(this, SIGNAL(isSelectedChanged()), SLOT(onChangeSelect()));
}

Element::~Element() {

}

QRectF Element::boundingRect() const {
    return QRectF(-48, -25, 97, 50);
}

QPointF Element::deltaMouseCoord() const {
    return m_deltaMouseCoord;
}

void Element::setDeltaMouseCoord(const QPointF deltaMouseCoord) {
    m_deltaMouseCoord = deltaMouseCoord;
    emit deltaMouseCoordChanged();
}

bool Element::isSelected() const {
    return m_isSelected;
}

void Element::setIsSelected(const bool isSelected) {
    m_isSelected = isSelected;
    emit isSelectedChanged();
}

void Element::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    setDeltaMouseCoord(this->scenePos() - event->scenePos());
    if (event->button() == Qt::LeftButton) {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
    } else if (event->button() == Qt::RightButton) {
        emit onSelectElement(this);
        setIsSelected(!m_isSelected);
        event->ignore();
    }
}

void Element::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QPointF position = event->pos();
    int x = position.x();
    int y = position.y();
    x = floor((position.x() + m_deltaMouseCoord.x()) / 25 + 0.5) * 25;
    y = floor((position.y() + m_deltaMouseCoord.y()) / 25 + 0.5) * 25;
    this->setPos(mapToScene(QPointF(x, y)));
    if(this->x() - 20 < 0) {
        this->setX(25);
    }
    if(this->x() + 20 > 1000) {
        this->setX(975);
    }
    if(this->y() - 20 < 0) {
        this->setY(25);
    }
    if(this->y() + 20 > 1000) {
        this->setY(975);
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Element::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    qDebug() << this->pos();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Element::onChangeSelect() {
    update();
}
