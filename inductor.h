#ifndef INDUCTOR_H
#define INDUCTOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "element.h"

class Inductor : public Element
{
    Q_OBJECT

    Q_PROPERTY(int inductance
               READ inductance WRITE setInductance
               NOTIFY inductanceChanged)
public:
    explicit Inductor(QObject *parent = 0);
    ~Inductor();

    int inductance() const;
    void setInductance(const int type);

signals:
    void inductanceChanged();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int m_inductance = 10;
};

#endif // INDUCTOR_H
