#include "Befehlrotieren.h"

Befehlrotieren::Befehlrotieren(BildModel* model, int rotationFactor)
    :oldRotationFactor(model->getRotationFactor()),
    newRotationFactor(rotationFactor)
    ,model(model)
{
    setText(QString("The picture has rotated %1 degrees").arg(rotationFactor));
}

void Befehlrotieren::undo()
{
    model->rotateImage(oldRotationFactor);
}

void Befehlrotieren::redo()
{
    model->rotateImage(newRotationFactor);
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
