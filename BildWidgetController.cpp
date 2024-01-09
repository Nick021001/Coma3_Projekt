#include "BildWidgetController.h"
#include "Befehlrotieren.h"
#include "Befehlskalieren.h"

Bildwidgetcontroller::Bildwidgetcontroller(BildModell* modell, QUndoStack* undostack ,BildView* view, QObject *parent):
    QObject(parent),
    pmodell(modell),
    pview(view),
    undostack(undostack)
{}

void Bildwidgetcontroller::pushRotationAfterRealse(int rotationFactor)
{
    auto cmd = new Befehlrotieren(pmodell, rotationFactor);
    undostack->push(cmd);
}

void Bildwidgetcontroller::pushScaleafterChange(int scaleFactor)
{
    auto cmd = new Befehlskalieren(pmodell, scaleFactor);
    undostack->push(cmd);
}
