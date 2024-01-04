#ifndef BILDCONTROLLER_H
#define BILDCONTROLLER_H

#include <QObject>
#include <QMouseEvent>
#include <QEvent>
#include <QRubberBand>

class BildModell;
class BildView;

class BildController: public QObject
{
    Q_OBJECT
    BildModell* pmodell;
    BildView* pview;
    QRubberBand* rubber = nullptr;
    QPoint rectStartPos;

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

public:
    BildController(BildModell* modell, BildView* view, QObject *parent);
};

#endif // BILDCONTROLLER_H
