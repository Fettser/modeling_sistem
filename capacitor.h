#ifndef CAPACITOR_H
#define CAPACITOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "element.h"

class Capacitor : public Element
{
    Q_OBJECT

    Q_PROPERTY(QString capacity
               READ capacity WRITE setCapacity
               NOTIFY capacityChanged)

public:
    explicit Capacitor(QObject *parent = 0, QString capacity = "10 pF");
    ~Capacitor();

    QString capacity() const;
    void setCapacity(const QString capacity);

signals:
    void capacityChanged();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QString m_capacity = "10 pF";
};

#endif // CAPACITOR_H
