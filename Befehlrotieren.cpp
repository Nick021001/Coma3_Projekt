#include "Befehlrotieren.h"

Befehlrotieren::Befehlrotieren(BildModell* modell, int rotationFactor)
    :rotationFactor(rotationFactor)
    ,modell(modell)
{
    setText(QString("Bild um %1 Grad gedreht").arg(rotationFactor));
}

void Befehlrotieren::undo()
{
    modell->setRotationFactor(0);
    modell->performTransformation();
}

void Befehlrotieren::redo()
{
    modell->setRotationFactor(this->rotationFactor);
    modell->performTransformation();
}
