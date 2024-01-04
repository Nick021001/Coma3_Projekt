#include "Befehlanimation.h"

BefehlAnimation::BefehlAnimation(BildModell* modell, MementoPtr alterZustand, MementoPtr neuerZustand)
    : modell(modell)
    , alterZustand(std::move(alterZustand))
    , neuerZustand(std::move(neuerZustand))
{
    setText("Animation");
}

void BefehlAnimation::undo()
{
    modell->setMemento(*alterZustand);
}

void BefehlAnimation::redo()
{
    modell->setMemento(*neuerZustand);
}
