#ifndef BEFEHLROTIEREN_H
#define BEFEHLROTIEREN_H

#include "BildModell.h"
#include <QUndoCommand>

class Befehlrotieren: public QUndoCommand
{
public:
    Befehlrotieren(BildModell* modell, int rotationFactor);

    void undo() override;
    void redo() override;

private:
    int rotationFactor;
    BildModell* modell = nullptr;

};


#endif // BEFEHLROTIEREN_H
