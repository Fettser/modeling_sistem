#include "switch.h"
#include <QPainter>
#include <QCursor>
#include <QPixmap>

Switch::Switch(QObject *parent) :
    Element(parent)
{
    setObjectName("switch");
}
Switch::~Switch() {

}

void Switch::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
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
    painter->drawLine(-48, 0, -20, 0);
    painter->drawLine(20, 0, 49, 0);
    painter->drawLine(-19, 0, 15, -15);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


