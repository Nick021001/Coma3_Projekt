#ifndef BEFEHLSKALIEREN_H
#define BEFEHLSKALIEREN_H

#include <QUndoCommand>
#include "BildModel.h"

class Befehlskalieren: public QUndoCommand
{
    int oldScaleFactor = 1;
    int newScaleFactor;
    BildModel* pmodel;

public:
    Befehlskalieren(BildModel* model, int scaleFactor);

    void undo() override;
    void redo() override;
    int id() const override;
    bool mergeWith(const QUndoCommand* other) override;
};

#endif // BEFEHLSKALIEREN_H
