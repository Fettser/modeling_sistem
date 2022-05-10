#ifndef BATTERY_H
#define BATTERY_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "element.h"

class Battery : public Element
{
    Q_OBJECT

    Q_PROPERTY(int resistance
               READ resistance WRITE setResistance
               NOTIFY resistanceChanged)

    Q_PROPERTY(int voltage
               READ voltage WRITE setVoltage
               NOTIFY voltageChanged)
public:
    explicit Battery(QObject *parent = 0);
    ~Battery();

    int resistance() const;
    void setResistance(const int type);
    int voltage() const;
    void setVoltage(const int type);

signals:
    void resistanceChanged();
    void voltageChanged();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int m_resistance = 1;
    int m_voltage = 5;
};

#endif // BATTERY_H
