#ifndef RESISTOR_H
#define RESISTOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "element.h"

class Resistor : public Element
{
    Q_OBJECT

    Q_PROPERTY(int resistance
               READ resistance WRITE setResistance
               NOTIFY resistanceChanged)
public:
    explicit Resistor(QObject *parent = 0);
    ~Resistor();

    int resistance() const;
    void setResistance(const int res);

signals:
    void resistanceChanged();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int m_resistance = 10;
};

#endif // RESISTOR_H
