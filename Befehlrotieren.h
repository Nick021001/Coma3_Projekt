#ifndef BEFEHLROTIEREN_H
#define BEFEHLROTIEREN_H

#include "BildModel.h"
#include <QUndoCommand>

class Befehlrotieren: public QUndoCommand
{
    int oldRotationFactor = 0;
    int newRotationFactor;
    BildModel* model = nullptr;

public:
    Befehlrotieren(BildModel* model, int rotationFactor);

    void undo() override;
    void redo() override;

    int id() const override;
    bool mergeWith(const QUndoCommand* other) override;
};


#endif // BEFEHLROTIEREN_H
