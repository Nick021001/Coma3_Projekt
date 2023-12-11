#include "BildController.h"

#include "BildModell.h"
#include "BildView.h"

BildController::BildController(BildModell* modell, BildView* view, QObject *parent): QObject(parent), pmodell(modell), pview(view)
{
    pview->installEventFilter(this);
}

void BildController::mousePressEvent(QMouseEvent* event)
{
    pmodell->setPos(event->pos());
}

void BildController::mouseReleaseEvent(QMouseEvent* event)
{}

bool BildController::eventFilter(QObject* watched, QEvent* event)
{
    return false;
}
