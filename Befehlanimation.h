#ifndef BEFEHLANIMATION_H
#define BEFEHLANIMATION_H

#include <QUndoCommand>

#include "BildModell.h"


class BefehlAnimation;

/*: public QUndoCommand
{
public:
    using MementoPtr = BildModell::MementoPtr;
    BefehlAnimation(BildModell* modell, MementoPtr alterZustand, MementoPtr neuerZustand);

private:
    BildModell* modell = nullptr;
    MementoPtr alterZustand;
    MementoPtr neuerZustand;

public:
    void undo() override;
    void redo() override;
};

*/
#endif // BEFEHLANIMATION_H
