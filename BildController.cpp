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
    if (!rubber)
        rubber = new QRubberBand(QRubberBand::Rectangle, this->pview);
    rubber->setGeometry(QRect(this->pmodell->getPos(), QSize()));
    rubber->show();
}

void BildController::mouseMoveEvent(QMouseEvent *event)
{
    rubber->setGeometry(QRect(this->pmodell->getPos(), event->pos()).normalized());
}

void BildController::mouseReleaseEvent(QMouseEvent *event)
{
    rubber->hide();
    this->pmodell->zoomInImage(QRect(this->pmodell->getPos(), event->pos()), this->pmodell->getPos());
}

bool BildController::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == pview) {
        if (event->type() == QEvent::MouseButtonPress) {
            mousePressEvent(static_cast<QMouseEvent*>(event));
        } else if (event->type() == QEvent::MouseMove) {
            mouseMoveEvent(static_cast<QMouseEvent*>(event));
        } else if (event->type() == QEvent::MouseButtonRelease) {
            mouseReleaseEvent(static_cast<QMouseEvent*>(event));
        }
    }

    return QObject::eventFilter(watched, event);
}
