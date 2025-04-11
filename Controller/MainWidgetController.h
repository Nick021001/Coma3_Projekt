#ifndef MAINWIDGETCONTROLLER_H
#define MAINWIDGETCONTROLLER_H

#include "BildModel.h"
#include "BildView.h"

#include <QUndoStack>
#include <QObject>

class Mainwidgetcontroller: public QObject
{
    Q_OBJECT
    BildModel* pmodel;
    BildView* pview;
    QUndoStack* undostack = nullptr;

public slots:
    void pushRotationAfterRelease(int rotationFactor);
    void pushScaleAfterChange(int scaleFactor);
    void setGreyScaleOnOff();
    void setEdgeDetectionOnOff();
    void setResetImage();
    void uploadImage();
    void saveImage();

public:
    Mainwidgetcontroller(BildModel* model, QUndoStack* undostack ,BildView* view, QObject *parent);
};

#endif // MAINWIDGETCONTROLLER_H
