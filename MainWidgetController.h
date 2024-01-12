#ifndef MAINWIDGETCONTROLLER_H
#define MAINWIDGETCONTROLLER_H

#include "BildModell.h"
#include "BildView.h"

#include <QUndoStack>
#include <QObject>

class Mainwidgetcontroller: public QObject
{
    Q_OBJECT
    BildModell* pmodell;
    BildView* pview;
    QUndoStack* undostack = nullptr;

public slots:
    void pushRotationAfterRealse(int rotationFactor);
    void pushScaleafterChange(int scaleFactor);
    void setGreyScaleOnOff();
    void setEdgeDeketionOnOff();
    void setResetImage();
    void uploadImage();
    void saveImage();

public:
    Mainwidgetcontroller(BildModell* modell, QUndoStack* undostack ,BildView* view, QObject *parent);
};

#endif // MAINWIDGETCONTROLLER_H
