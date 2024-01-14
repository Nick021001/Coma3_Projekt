#include "Befehlskalieren.h"

Befehlskalieren::Befehlskalieren(BildModel* model, int scaleFactor)
    :oldScaleFactor(model->getScaleFactor()),
    newScaleFactor(scaleFactor)
    ,pmodel(model)
{
    this->setText(QString("The picture was scaled with the factor %1").arg(scaleFactor));
}

void Befehlskalieren::undo()
{
    pmodel->scaleImage(oldScaleFactor);
}

void Befehlskalieren::redo()
{
    pmodel->scaleImage(newScaleFactor);
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
