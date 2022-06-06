#ifndef RESISTOR_H
#define RESISTOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "element.h"

class Resistor : public Element
{
    Q_OBJECT

    Q_PROPERTY(QString resistance
               READ resistance WRITE setResistance
               NOTIFY resistanceChanged)
public:
    explicit Resistor(QObject *parent = 0, QString resistance = "10 Om");
    ~Resistor();

    QString resistance() const;
    void setResistance(const QString res);

signals:
    void resistanceChanged();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QString m_resistance = "10 Om";
};

#endif // RESISTOR_H
