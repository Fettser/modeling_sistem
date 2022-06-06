#ifndef INDUCTOR_H
#define INDUCTOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "element.h"

class Inductor : public Element
{
    Q_OBJECT

    Q_PROPERTY(QString inductance
               READ inductance WRITE setInductance
               NOTIFY inductanceChanged)
public:
    explicit Inductor(QObject *parent = 0, QString inductance = "10 mG");
    ~Inductor();

    QString inductance() const;
    void setInductance(const QString inductance);

signals:
    void inductanceChanged();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QString m_inductance = "10 mG";
};

#endif // INDUCTOR_H
