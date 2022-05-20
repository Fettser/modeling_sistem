#ifndef CAPACITOR_H
#define CAPACITOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "element.h"

class Capacitor : public Element
{
    Q_OBJECT

    Q_PROPERTY(int capacity
               READ capacity WRITE setCapacity
               NOTIFY capacityChanged)
public:
    explicit Capacitor(QObject *parent = 0);
    ~Capacitor();

    int capacity() const;
    void setCapacity(const int type);

signals:
    void capacityChanged();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int m_capacity = 10;
};

#endif // CAPACITOR_H
