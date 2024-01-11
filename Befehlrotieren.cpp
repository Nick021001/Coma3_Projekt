#include "Befehlrotieren.h"

Befehlrotieren::Befehlrotieren(BildModell* modell, int rotationFactor)
    :oldRotationFactor(modell->getRotationFactor()),
    newRotationFactor(rotationFactor)
    ,modell(modell)
{
    setText(QString("The picture has rotated %1 degrees").arg(rotationFactor));
}

void Befehlrotieren::undo()
{
    modell->rotateImage(oldRotationFactor);
}

void Befehlrotieren::redo()
{
    modell->rotateImage(newRotationFactor);
}

int Befehlrotieren::id() const
{
    return 1;
}

bool Befehlrotieren::mergeWith(const QUndoCommand* other)
{
    if(auto cmd = dynamic_cast<const Befehlrotieren*>(other))
    {
        newRotationFactor = cmd->newRotationFactor;
        setText(QString("The picture has rotated %1 degrees").arg(newRotationFactor));
        return true;
    }
    return false;
}
