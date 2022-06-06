#ifndef SWITCH_H
#define SWITCH_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "element.h"

class Switch : public Element
{
    Q_OBJECT

public:
    explicit Switch(QObject *parent = 0);
    ~Switch();

signals:

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // SWITCH_H
