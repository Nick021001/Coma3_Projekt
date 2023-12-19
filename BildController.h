#ifndef BILDCONTROLLER_H
#define BILDCONTROLLER_H

#include <QObject>
#include <QMouseEvent>
#include <QEvent>

class BildModell;
class BildView;
class QRubberBand;

class BildController: public QObject
{
    Q_OBJECT
    BildModell* pmodell;
    BildView* pview;
    QRubberBand* rubberBand = nullptr;

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);

public:
    BildController(BildModell* modell, BildView* view, QObject *parent);

    /*
public:
    bool eventFilter(QObject* watched, QEvent* event) override;
*/
};

#endif // BILDCONTROLLER_H
