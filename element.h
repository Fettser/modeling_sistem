#ifndef ELEMENT_H
#define ELEMENT_H
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsPixmapItem>

class Element: public QObject, public QGraphicsItem {

    Q_OBJECT

    Q_PROPERTY(QPointF deltaMouseCoord
               READ deltaMouseCoord WRITE setDeltaMouseCoord
               NOTIFY deltaMouseCoordChanged)

    Q_PROPERTY(bool isSelected
               READ isSelected WRITE setIsSelected
               NOTIFY isSelectedChanged)

public:
    explicit Element(QObject *parent = 0);
    ~Element();

    QPointF deltaMouseCoord() const;
    void setDeltaMouseCoord(const QPointF deltaMouseCoord);

    bool isSelected() const;
    void setIsSelected(const bool isSelected);

signals:
    void onSelectElement(QGraphicsItem *el);
    void onRotateElement(QGraphicsItem *el);
    void deltaMouseCoordChanged();
    void isSelectedChanged();

private slots:
    void onChangeSelect();

protected:
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QPointF m_deltaMouseCoord = QPointF(0,0);
    bool m_isSelected;
};

#endif // ELEMENT_H
