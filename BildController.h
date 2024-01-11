#ifndef BILDCONTROLLER_H
#define BILDCONTROLLER_H

#include <QObject>
#include <QMouseEvent>
#include <QEvent>
#include <QRubberBand>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class BildModell;
class BildView;
class QUndoStack;

class BildController: public QObject
{
    Q_OBJECT
    BildModell* pmodell;
    BildView* pview;

    QUndoStack* undostack = nullptr;
    // Deklaration der Lupe
    QGraphicsView* magnifierView;
    QGraphicsScene* magnifierScene;
    QGraphicsPixmapItem* magnifiedItem;

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
    int adaptRotationFactor(int rotationFactor); // sorgt dafür das der Rotationsfactor immer zwischen 0 und 360 grad liegt.

public:
    BildController(BildModell* modell, QUndoStack* undostack, BildView* view, QObject *parent);
};

#endif // BILDCONTROLLER_H
