#include "BildController.h"
#include "BildModel.h"
#include "BildView.h"
#include "Befehlrotieren.h"
#include "Befehlskalieren.h"

#include <QUndoStack>

BildController::BildController(BildModel* model, QUndoStack* undostack ,BildView* view, QObject *parent):
    QObject(parent),
    pmodel(model),
    pview(view),
    undostack(undostack)
{
    magnifierView = new QGraphicsView();
    magnifierScene = new QGraphicsScene();
    magnifierView->setScene(magnifierScene);
    magnifierView->setFixedSize(200, 200); // Größe der Lupe anpassen
    magnifierView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    magnifierView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    magnifiedItem = magnifierScene->addPixmap(QPixmap());
    magnifiedItem->setScale(2.0); // Vergrößerungsfaktor anpassen
    magnifierView->hide();
    pview->installEventFilter(this);
}

int BildController::adaptRotationFactor(int rotationFactor)
{
    if (rotationFactor > 360)
        rotationFactor = rotationFactor - 360;
    if (rotationFactor < 0)
        rotationFactor = rotationFactor + 360;

    return rotationFactor;
}

int BildController::adaptScaleFactor(int scaleFactor)
{
    scaleFactor = qBound(1, scaleFactor, 6);

    return scaleFactor;
}

void BildController::mousePressEvent(QMouseEvent *event)
{
    magnifierView->show();
}

void BildController::mouseMoveEvent(QMouseEvent *event)
{
    QPointF magnifierPosition = event->pos();
    QImage image = pmodel->getImage().copy(
        magnifierPosition.x() - 25, // Anpassen des Ausschnitts in der Lupe
        magnifierPosition.y() - 25, // Anpassen des Ausschnitts in der Lupe
        200, // Größe des Ausschnitts in der Lupe anpassen
        200 // Größe des Ausschnitts in der Lupe anpassen
        );
    magnifiedItem->setPixmap(QPixmap().fromImage(image));
    magnifierView->move(event->globalPosition().x() + 20, event->globalPosition().y() + 20); // Lupe der Maus folgen lassen
}

void BildController::mouseReleaseEvent(QMouseEvent *event)
{
    magnifierView->hide();
}

void BildController::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Plus:
    {
        int scalefactor = pmodel->getScaleFactor()  + 1;
        scalefactor = this->adaptScaleFactor(scalefactor);
        this->pushScaleToStack(scalefactor);
        break;
    }
    case Qt::Key_Minus:
    {
        int scalefactor = pmodel->getScaleFactor() -1;
        scalefactor = this->adaptScaleFactor(scalefactor);
        this->pushScaleToStack(scalefactor);
        break;
    }
    case Qt::Key_Up:
    {
        int rotationfactor = pmodel->getRotationFactor() + 180;
        rotationfactor = this->adaptRotationFactor(rotationfactor);
        this->pushRotationToStack(rotationfactor);
        break;
    }
    case Qt::Key_Down:
    {
        int rotationfactor = pmodel->getRotationFactor() - 180;
        rotationfactor = this->adaptRotationFactor(rotationfactor);
        this->pushRotationToStack(rotationfactor);
        break;
    }
    case Qt::Key_Left:
    {
        int rotationfactor = pmodel->getRotationFactor() - 90;
        rotationfactor = this->adaptRotationFactor(rotationfactor);
        this->pushRotationToStack(rotationfactor);
        break;
    }
    case Qt::Key_Right:
    {
        int rotationfactor = pmodel->getRotationFactor() + 90;
        rotationfactor = this->adaptRotationFactor(rotationfactor);
        this->pushRotationToStack(rotationfactor);
        break;
    }
    case Qt::Key_G:     //Greyscale
        pmodel->grayscaleOnOff();
        break;

    case Qt::Key_E:     //Edgedetection
        pmodel->edgeDetectionOnOff();
        break;

    case Qt::Key_Backspace:    //reset
        pmodel->resetImage();
        break;

    case Qt::Key_Return: //save
        pmodel->save();
        break;
    }
}

bool BildController::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == pview) {
        switch(event->type())
        {
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

void BildController::pushRotationToStack(int rotationFactor)
{
    auto cmd = new Befehlrotieren(pmodel, rotationFactor);
    undostack->push(cmd);
}

void BildController::pushScaleToStack(int scaleFactor)
{
    auto cmd = new Befehlskalieren(pmodel, scaleFactor);
    undostack->push(cmd);
}
