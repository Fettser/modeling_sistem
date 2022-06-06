#ifndef BATTERY_H
#define BATTERY_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "element.h"

class Battery : public Element
{
    Q_OBJECT

    Q_PROPERTY(QString resistance
               READ resistance WRITE setResistance
               NOTIFY resistanceChanged)

    Q_PROPERTY(QString voltage
               READ voltage WRITE setVoltage
               NOTIFY voltageChanged)

public:
    explicit Battery(QObject *parent = 0, QString voltage = "5 V", QString resistance = "1 Om");
    ~Battery();

    QString resistance() const;
    void setResistance(const QString resistance);
    QString voltage() const;
    void setVoltage(const QString voltage);

signals:
    void resistanceChanged();
    void voltageChanged();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QString m_resistance = "1 Om";
    QString m_voltage = "5 V";
};

#endif // BATTERY_H
