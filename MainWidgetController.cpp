#include "MainWidgetController.h"
#include "Befehlrotieren.h"
#include "Befehlskalieren.h"

Mainwidgetcontroller::Mainwidgetcontroller(BildModel* model, QUndoStack* undostack ,BildView* view, QObject *parent):
    QObject(parent),
    pmodel(model),
    pview(view),
    undostack(undostack)
{}

void Mainwidgetcontroller::pushRotationAfterRelease(int rotationFactor)
{
    auto cmd = new Befehlrotieren(pmodel, rotationFactor);
    undostack->push(cmd);
}

void Mainwidgetcontroller::pushScaleAfterChange(int scaleFactor)
{
    auto cmd = new Befehlskalieren(pmodel, scaleFactor);
    undostack->push(cmd);
}

void Mainwidgetcontroller::setGreyScaleOnOff()
{
    pmodel->grayscaleOnOff();
}

void Mainwidgetcontroller::setEdgeDetectionOnOff()
{
    pmodel->edgeDetectionOnOff();
}

void Mainwidgetcontroller::setResetImage()
{
    pmodel->resetImage();
}

void Mainwidgetcontroller::uploadImage()
{
    pmodel->upload();
}

void Mainwidgetcontroller::saveImage()
{
    pmodel->save();
}
