#include "BildController.h"

#include "BildModell.h"
#include "BildView.h"
#include "Befehlausschneiden.h"
#include "Befehlrotieren.h"
#include "Befehlskalieren.h"

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

void BildController::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Plus:
    {
        int scalefactor = pmodell->getScaleFactor()  + 1;
        auto cmd = new Befehlskalieren(pmodell, scalefactor);
        undostack->push(cmd);
        break;
    }
    case Qt::Key_Minus:
    {
        int scalefactor = pmodell->getScaleFactor() -1;
        auto cmd = new Befehlskalieren(pmodell, scalefactor);
        undostack->push(cmd);
        break;
    }
    break;
    case Qt::Key_Up:
    {
        int rotationfactor = pmodell->getRotationFactor() + 180;
        auto cmd = new Befehlrotieren(pmodell, rotationfactor);
        undostack->push(cmd);
        break;
    }
    break;
    case Qt::Key_Down:
    {
        int rotationfactor = pmodell->getRotationFactor() + 180;
        auto cmd = new Befehlrotieren(pmodell, rotationfactor);
        undostack->push(cmd);
        break;
    }
    break;

    case Qt::Key_Left:
    {
        int rotationfactor = pmodell->getRotationFactor() - 90;
        auto cmd = new Befehlrotieren(pmodell, rotationfactor);
        undostack->push(cmd);
        break;
    }
    case Qt::Key_Right:
    {
        int rotationfactor = pmodell->getRotationFactor() + 90;
        auto cmd = new Befehlrotieren(pmodell, rotationfactor);
        undostack->push(cmd);
        break;
    }

    case Qt::Key_G:     //Greyscale
        pmodell->grayscaleOnOff();
        break;

    case Qt::Key_E:     //Edgedetection
        pmodell->edgeDetektionOnOff();
        break;

    case Qt::Key_Backspace:    //reset
        pmodell->resetImage();
        break;

    case Qt::Key_Escape:        //close
        break;

    case Qt::Key_Return: //save
        pmodell->speichern();
        break;
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
        case QEvent::KeyPress:
            keyPressEvent(dynamic_cast<QKeyEvent*>(event));
            break;
        default:
            return false;
        }
    }

    return QObject::eventFilter(watched, event);
}
