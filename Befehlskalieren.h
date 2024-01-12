#ifndef BEFEHLSKALIEREN_H
#define BEFEHLSKALIEREN_H

#include <QUndoCommand>
#include "BildModell.h"

class Befehlskalieren: public QUndoCommand
{
    int oldScaleFactor = 1;
    int newScaleFactor;
    BildModell* pmodell;

public:
    Befehlskalieren(BildModell* modell, int scaleFactor);

    void undo() override;
    void redo() override;
    int id() const override;
    bool mergeWith(const QUndoCommand* other) override;
};

#endif // BEFEHLSKALIEREN_H
