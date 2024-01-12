#include "MainWidgetController.h"
#include "Befehlrotieren.h"
#include "Befehlskalieren.h"

Mainwidgetcontroller::Mainwidgetcontroller(BildModell* modell, QUndoStack* undostack ,BildView* view, QObject *parent):
    QObject(parent),
    pmodell(modell),
    pview(view),
    undostack(undostack)
{}

void Mainwidgetcontroller::pushRotationAfterRealse(int rotationFactor)
{
    auto cmd = new Befehlrotieren(pmodell, rotationFactor);
    undostack->push(cmd);
}

void Mainwidgetcontroller::pushScaleafterChange(int scaleFactor)
{
    auto cmd = new Befehlskalieren(pmodell, scaleFactor);
    undostack->push(cmd);
}

void Mainwidgetcontroller::setGreyScaleOnOff()
{
    pmodell->grayscaleOnOff();
}

void Mainwidgetcontroller::setEdgeDeketionOnOff()
{
    pmodell->edgeDetektionOnOff();
}

void Mainwidgetcontroller::setResetImage()
{
    pmodell->resetImage();
}

void Mainwidgetcontroller::uploadImage()
{
    pmodell->upload();
}

void Mainwidgetcontroller::saveImage()
{
    pmodell->save();
}
