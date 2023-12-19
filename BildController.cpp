#include "BildController.h"

#include "BildModell.h"
#include "BildView.h"
#include <QRubberBand>

BildController::BildController(BildModell* modell, BildView* view, QObject *parent): QObject(parent), pmodell(modell), pview(view)
{
    pview->installEventFilter(this);
}

void BildController::mousePressEvent(QMouseEvent *event)
{
    this->pmodell->setPos(event->pos());
    if (!rubberBand)
        this->rubberBand = new QRubberBand(QRubberBand::Rectangle);
    rubberBand->setGeometry(QRect(this->pmodell->getPos(), QSize()));
    rubberBand->show();
}

void BildController::mouseMoveEvent(QMouseEvent *event)
{
    rubberBand->setGeometry(QRect(this->pmodell->getPos(), event->pos()).normalized());
}

void BildController::mouseReleaseEvent(QMouseEvent *event)
{
    rubberBand->hide();
    // determine selection, for example using QRect::intersects()
    // and QRect::contains().
}

/*
bool BildController::eventFilter(QObject* watched, QEvent* event)
{
    return false;
}
*/
