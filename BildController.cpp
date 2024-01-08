#include "BildController.h"

#include "BildModell.h"
#include "BildView.h"
#include "Befehlausschneiden.h"

#include <QUndoStack>
#include <QRubberBand>
#include <QVector2D>

BildController::BildController(BildModell* modell, QUndoStack* undostack ,BildView* view, QObject *parent):
    QObject(parent),
    pmodell(modell),
    pview(view),
    undostack(undostack)
{
    pview->installEventFilter(this);
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
    if (rectStartPos == event->pos())
    {
        qDebug() << "single Pixel can not be displayed";
    }

    else
    {
        if (QVector2D(rectStartPos).length() > QVector2D(event->pos()).length())
        {
            QPoint endPos = rectStartPos;
            rectStartPos = event->pos();
            auto cmd = new Befehlausschneiden(pmodell, QRect(rectStartPos, endPos));
            undostack->push(cmd);
        }

        else
        {
            auto cmd = new Befehlausschneiden(pmodell, QRect(rectStartPos, event->pos()));
            undostack->push(cmd);
        }
    }

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
        /*
        case QEvent::KeyPress:
            keyPressEvent(dynamic_cast<QKeyEvent*>(event));
            break;
        */
        default:
            return false;
        }
    }

    return QObject::eventFilter(watched, event);
}
