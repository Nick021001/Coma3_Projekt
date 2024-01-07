#include "BildController.h"

#include "BildModell.h"
#include "BildView.h"
#include "Befehlausschneiden.h"

#include <QUndoStack>
#include <QRubberBand>

BildController::BildController(BildModell* modell, QUndoStack* undostack ,BildView* view, QObject *parent):
    QObject(parent),
    pmodell(modell),
    pview(view),
    undostack(undostack)
{
    pview->installEventFilter(this);
}

bool BildController::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == pview) {
        switch(event->type()) // Bestimmen des Ereignistyps (siehe auch Folien zur Ereignisbehandlung)
        {
        // relevante Ereignistypen behandeln:
        // cast auf speziellen Typ durchführen und die speziellen Event-Methoden aufrufen (der Übersichtlichkeitshalber)
        case QEvent::MouseButtonPress:
            mousePressEvent(dynamic_cast<QMouseEvent*>(event));
            break;
        case QEvent::MouseMove:
            mouseMoveEvent(dynamic_cast<QMouseEvent*>(event));
            break;
        case QEvent::MouseButtonRelease:
            mouseReleaseEvent(dynamic_cast<QMouseEvent*>(event));
            break;
        case QEvent::KeyPress:
            keyPressEvent(dynamic_cast<QKeyEvent*>(event));
            break;
        default:
            return false;
        }
    }

    return QObject::eventFilter(watched, event);
}

void BildController::mousePressEvent(QMouseEvent *event)
{
    rectStartPos = event->pos();
    if (!rubber)
        rubber = new QRubberBand(QRubberBand::Rectangle, pview);
    rubber->setGeometry(QRect(rectStartPos, QSize()));
    rubber->show();
}

void BildController::mouseMoveEvent(QMouseEvent *event)
{
    rubber->setGeometry(QRect(rectStartPos, event->pos()).normalized());
}

void BildController::mouseReleaseEvent(QMouseEvent *event)
{
    rubber->hide();
    //this->pmodell->zoomInImage(QRect(rectStartPos, event->pos()));
    auto cmd = new Befehlausschneiden(pmodell, QRect(rectStartPos, event->pos()));
    undostack->push(cmd);
}

void BildController::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Plus:
    {
        pmodell->setRotationFactor(pmodell->getRotationFactor() + 90);
        pmodell->performTransformation();
        break;
    }

    case Qt::Key_Minus:
    {
        pmodell->setRotationFactor(pmodell->getRotationFactor() - 90);
        pmodell->performTransformation();
        break;
    }
    }
}
