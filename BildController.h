#ifndef BILDCONTROLLER_H
#define BILDCONTROLLER_H

#include <QObject>
#include <QMouseEvent>
#include <QEvent>
#include <QRubberBand>
#include <QKeyEvent>

class BildModell;
class BildView;
class QUndoStack;

class BildController: public QObject
{
    Q_OBJECT
    BildModell* pmodell;
    BildView* pview;
    QRubberBand* rubber = nullptr;
    QPoint rectStartPos;
    QUndoStack* undostack = nullptr;

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent* event);
    bool eventFilter(QObject *watched, QEvent *event);

public:
    BildController(BildModell* modell, QUndoStack* undostack, BildView* view, QObject *parent);
};

#endif // BILDCONTROLLER_H
