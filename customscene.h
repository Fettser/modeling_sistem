#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>

class CustomScene : public QGraphicsScene {
    Q_OBJECT
    Q_PROPERTY(int typeElement
               READ typeElement WRITE setTypeElement
               NOTIFY typeElementChanged)

    Q_PROPERTY(QPointF previousPosition
               READ previousPosition WRITE setPreviousPosition
               NOTIFY previousPositionChanged)
    Q_PROPERTY(QPointF nextPosition
               READ nextPosition WRITE setNextPosition
               NOTIFY nextPositionChanged)

public:
    explicit CustomScene(QObject *parent = 0);
    ~CustomScene();

    int typeElement() const;
    void setTypeElement(const int type);

    QPointF previousPosition() const;
    void setPreviousPosition(const QPointF previousPosition);

    QPointF nextPosition() const;
    void setNextPosition(const QPointF nextPosition);

    enum ElementTypes {
        BatteryType,
        ResistorType,
        WireType
    };

signals:
    void typeElementChanged();
    void resetEl();
    void previousPositionChanged();
    void nextPositionChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    int m_typeElement;
    QPointF m_previousPosition;
    QPointF m_nextPosition;
    QGraphicsItem *currentLine;
    bool m_leftMouseButtonPressed;
};

#endif // CUSTOMSCENE_H
