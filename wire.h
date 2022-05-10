#ifndef WIRE_H
#define WIRE_H
#include <QObject>
#include <QGraphicsLineItem>

class Wire: public QObject, public QGraphicsLineItem {

    Q_OBJECT

public:
    explicit Wire(QObject *parent = 0);
    ~Wire();
signals:
    void onSelectElement(QGraphicsItem *el);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // WIRE_H
