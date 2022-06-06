#ifndef WIRE_H
#define WIRE_H
#include <QObject>
#include <QGraphicsLineItem>

class Wire: public QObject, public QGraphicsLineItem {

    Q_OBJECT

    Q_PROPERTY(QPointF firstPoint
               READ firstPoint WRITE setFirstPoint
               NOTIFY firstPointChanged)

    Q_PROPERTY(QPointF secondPoint
               READ secondPoint WRITE setSecondPoint
               NOTIFY secondPointChanged)

public:
    explicit Wire(QObject *parent = 0);
    explicit Wire(QObject *parent = 0, QPointF start = QPointF(0, 0), QPointF end = QPointF(0, 0));
    ~Wire();

    QPointF firstPoint() const;
    void setFirstPoint(const QPointF point);

    QPointF secondPoint() const;
    void setSecondPoint(const QPointF point);
signals:
    void onSelectElement(QGraphicsItem *el);
    void secondPointChanged();
    void firstPointChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    QPointF m_firstPoint;
    QPointF m_secondPoint;
};

#endif // WIRE_H
