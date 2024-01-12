#ifndef BEFEHLROTIEREN_H
#define BEFEHLROTIEREN_H

#include "BildModell.h"
#include <QUndoCommand>

class Befehlrotieren: public QUndoCommand
{
    int oldRotationFactor = 0;
    int newRotationFactor;
    BildModell* modell = nullptr;

public:
    Befehlrotieren(BildModell* modell, int rotationFactor);

    void undo() override;
    void redo() override;

    int id() const override;
    bool mergeWith(const QUndoCommand* other) override;
};


#endif // BEFEHLROTIEREN_H
