#ifndef BILDCONTROLLER_H
#define BILDCONTROLLER_H

#include <QObject>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

class BildModel;
class BildView;
class QUndoStack;

class BildController: public QObject
{
    Q_OBJECT
    BildModel* pmodel;
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
    void pushRotationToStack(int rotationFactor);
    void pushScaleToStack(int scaleFactor);
    int adaptRotationFactor(int rotationFactor); // sorgt dafür das der Rotationsfactor immer zwischen 0 und 360 grad liegt.
    int adaptScaleFactor(int scaleFactor);

public:
    BildController(BildModel* model, QUndoStack* undostack, BildView* view, QObject *parent);
};

#endif // BILDCONTROLLER_H
