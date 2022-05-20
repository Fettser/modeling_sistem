#include "customscene.h"
#include "resistor.h"
#include "capacitor.h"
#include "battery.h"
#include "inductor.h"
#include "math.h"
#include "wire.h"

static QPointF setElementPos(QPointF position) {
    int x = position.x();
    int y = position.y();
    x = floor(position.x() / 25 + 0.5) * 25;
    y = floor(position.y() / 25 + 0.5) * 25;
    if(x - 20 < 0) {
        x = 25;
    }
    if(x + 20 > 1000) {
        x = 975;
    }
    if(y - 20 < 0) {
        y = 25;
    }
    if(y + 20 > 1000) {
        y = 975;
    }
    return QPointF(x, y);
}

CustomScene::CustomScene(QObject *parent) :
    QGraphicsScene(parent),
    currentLine(nullptr),
    m_leftMouseButtonPressed(false)
{

}

CustomScene::~CustomScene() {
    delete currentLine;
}

QPointF CustomScene::previousPosition() const
{
    return m_previousPosition;
}

void CustomScene::setPreviousPosition(const QPointF previousPosition)
{
    if (m_previousPosition == previousPosition)
        return;

    m_previousPosition = previousPosition;
    emit previousPositionChanged();
}

QPointF CustomScene::nextPosition() const
{
    return m_previousPosition;
}

void CustomScene::setNextPosition(const QPointF nextPosition)
{
    if (m_nextPosition == nextPosition) {
        return;
    }
    m_nextPosition = nextPosition;
    emit nextPositionChanged();
}

int CustomScene::typeElement() const {
    return m_typeElement;
}

void CustomScene::setTypeElement(const int type) {
    m_typeElement = type;
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit resetEl();
    if (dynamic_cast<Element*>(this->itemAt(event->scenePos(), QTransform())) == nullptr) {
        if (event->button() == Qt::LeftButton) {
            switch (m_typeElement) {
            case BatteryType : {
                Battery *battery = new Battery(this);
                connect(battery, SIGNAL(onSelectElement(QGraphicsItem*)), parent(), SLOT(elementSelected(QGraphicsItem*)));
                battery->setPos(setElementPos(event->scenePos()));
                addItem(battery);
                break;
            }
            case ResistorType : {
                Resistor *resistor = new Resistor(this);
                connect(resistor, SIGNAL(onSelectElement(QGraphicsItem*)), parent(), SLOT(elementSelected(QGraphicsItem*)));
                resistor->setPos(setElementPos(event->scenePos()));
                addItem(resistor);
                break;
            }
            case CapacitorType: {
                Capacitor *capacitor = new Capacitor(this);
                connect(capacitor, SIGNAL(onSelectElement(QGraphicsItem*)), parent(), SLOT(elementSelected(QGraphicsItem*)));
                capacitor->setPos(setElementPos(event->scenePos()));
                addItem(capacitor);
                break;
            }
            case InductorType: {
                Inductor *inductor = new Inductor(this);
                connect(inductor, SIGNAL(onSelectElement(QGraphicsItem*)), parent(), SLOT(elementSelected(QGraphicsItem*)));
                inductor->setPos(setElementPos(event->scenePos()));
                addItem(inductor);
                break;
            }
            case WireType: {
                if (m_previousPosition.isNull() && m_nextPosition.isNull()) {
                    setNextPosition(setElementPos(event->scenePos()));
                    setPreviousPosition(setElementPos(event->scenePos()));
                } else {
                    setPreviousPosition(m_nextPosition);
                }
                m_leftMouseButtonPressed = true;
                Wire *line = new Wire(this);
                connect(line, SIGNAL(onSelectElement(QGraphicsItem*)), parent(), SLOT(elementSelected(QGraphicsItem*)));
                currentLine = line;
                line->setPen(QPen(Qt::black, 4, Qt::SolidLine));
                addItem(currentLine);
                line->setLine(QLineF(m_previousPosition, m_previousPosition));
                break;
            }
            default : {
                break;
            }
            }
        } else if (event->button() == Qt::RightButton) {
            if (dynamic_cast<QGraphicsLineItem*>(this->itemAt(event->scenePos(), QTransform())) != nullptr) {
                delete currentLine;
                currentLine = nullptr;
                QGraphicsScene::mousePressEvent(event);
            } else {
                if (m_typeElement != WireType) {
                    setTypeElement(6);
                }
            }
        }
    } else {
        QGraphicsScene::mousePressEvent(event);
    }
}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_leftMouseButtonPressed && m_typeElement == WireType && currentLine != nullptr) {

        QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem *>(currentLine);
        if (abs(m_previousPosition.x() - event->scenePos().x()) > abs(m_previousPosition.y() - event->scenePos().y())) {
            line->setLine(QLineF(m_previousPosition, QPointF(setElementPos(event->scenePos()).x(),
                                                             m_previousPosition.y())));
            setNextPosition(QPointF(setElementPos(event->scenePos()).x(),
                                    m_previousPosition.y()));
        } else {
            line->setLine(QLineF(m_previousPosition, QPointF(m_previousPosition.x(),
                                                             setElementPos(event->scenePos()).y())));
            setNextPosition(QPointF(m_previousPosition.x(),
                                    setElementPos(event->scenePos()).y()));
        }
    } else {
        QGraphicsScene::mouseMoveEvent(event);
    }
}

void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton && m_typeElement == WireType) {
        if (currentLine) {
            delete currentLine;
            currentLine = nullptr;
        }
        if (m_leftMouseButtonPressed){
            if (abs(m_previousPosition.x() - event->scenePos().x()) > abs(m_previousPosition.y() - event->scenePos().y())) {
                setPreviousPosition(QPointF(setElementPos(event->scenePos()).x(),
                                            m_previousPosition.y()));
            } else {
                setPreviousPosition(QPointF(m_previousPosition.x(),
                                            setElementPos(event->scenePos()).y()));
            }
        }
        m_leftMouseButtonPressed = false;
        setTypeElement(6);
    } else {
        QGraphicsScene::mouseReleaseEvent(event);
    }
}
