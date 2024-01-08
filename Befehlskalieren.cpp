#include "Befehlskalieren.h"

Befehlskalieren::Befehlskalieren(BildModell* modell, int scaleFactor)
    :scaleFactor(scaleFactor),
    pmodell(modell)
{
    this->setText(QString("The picture scale with the factor %1").arg(scaleFactor));
}

void Befehlskalieren::undo()
{
    pmodell->setScaleFactor(1);
    pmodell->performTransformation();
}


void Befehlskalieren::redo()
{
    pmodell->setScaleFactor(this->scaleFactor);
    pmodell->performTransformation();
}
