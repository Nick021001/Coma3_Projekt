#ifndef BILDCONTROLLER_H
#define BILDCONTROLLER_H

//test

#include <QObject>
#include <QMouseEvent>
#include <QEvent>

class BildModell;
class BildView;

class BildController: public QObject
{
    Q_OBJECT
    BildModell* pmodell;
    BildView* pview;

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public:
    BildController(BildModell* modell, BildView* view, QObject *parent);

public:
    bool eventFilter(QObject* watched, QEvent* event) override;

};

#endif // BILDCONTROLLER_H
