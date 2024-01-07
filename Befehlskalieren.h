#ifndef BEFEHLSKALIEREN_H
#define BEFEHLSKALIEREN_H

#include <QUndoCommand>
#include "BildModell.h"

class Befehlskalieren: public QUndoCommand
{
public:
    Befehlskalieren(BildModell* modell, int scaleFactor);

    void undo() override;
    void redo() override;

private:
    int scaleFactor;
    BildModell* pmodell;

};

#endif // BEFEHLSKALIEREN_H
