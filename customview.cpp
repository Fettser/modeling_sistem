#include "customview.h"

CustomView::CustomView(QWidget *parent) : QGraphicsView(parent) {
    setMouseTracking(true);
}

void CustomView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    double scaleFactor = 1.2;

    if(event->angleDelta().y() > 0) {
        if (zoom < 5) {
            zoom++;
            scale(scaleFactor, scaleFactor);
        }
    } else {
        if (zoom > -4) {
            zoom--;
            scale(1/scaleFactor, 1/scaleFactor);
        }
    }
}
