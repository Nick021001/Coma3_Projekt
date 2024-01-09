#include "Befehlskalieren.h"

Befehlskalieren::Befehlskalieren(BildModell* modell, int scaleFactor)
    :oldScaleFactor(modell->getScaleFactor()),
    newScaleFactor(scaleFactor)
    ,pmodell(modell)
{
    this->setText(QString("The picture was scaled with the factor %1").arg(scaleFactor));
}

void Befehlskalieren::undo()
{
    pmodell->scaleImage(oldScaleFactor);
}

void Befehlskalieren::redo()
{
    pmodell->scaleImage(newScaleFactor);
}

int Befehlskalieren::id() const
{
    return 1;
}
bool Befehlskalieren::mergeWith(const QUndoCommand* other)
{
    if(auto cmd = dynamic_cast<const Befehlskalieren*>(other))
    {
        newScaleFactor = cmd->newScaleFactor;
        setText(QString("The picture was scaled with the factor %1").arg(newScaleFactor));
        return true;

    }
    return false;
}
