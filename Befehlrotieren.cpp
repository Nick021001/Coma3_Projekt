#include "Befehlrotieren.h"

Befehlrotieren::Befehlrotieren(BildModell* modell, int rotationFactor)
    :rotationFactor(rotationFactor)
    ,modell(modell)
{
    setText(QString("Bild um %1 Grad gedreht").arg(rotationFactor));
}

void Befehlrotieren::undo()
{
    modell->rotateImage(rotationFactor);
}

void Befehlrotieren::redo()
{
    modell->rotateImage(rotationFactor);
}
