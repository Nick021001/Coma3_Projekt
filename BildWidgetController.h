#ifndef BILDWIDGETCONTROLLER_H
#define BILDWIDGETCONTROLLER_H

#include "BildModell.h"
#include "BildView.h"

#include <QUndoStack>
#include <QObject>

class Bildwidgetcontroller: public QObject
{
    Q_OBJECT
    BildModell* pmodell;
    BildView* pview;
    QUndoStack* undostack = nullptr;

public slots:
    void pushRotationAfterRealse(int rotationFactor);
    void pushScaleafterChange(int scaleFactor);

public:
    Bildwidgetcontroller(BildModell* modell, QUndoStack* undostack ,BildView* view, QObject *parent);
};

#endif // BILDWIDGETCONTROLLER_H
