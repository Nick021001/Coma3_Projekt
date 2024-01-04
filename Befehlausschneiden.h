#ifndef BEFEHLAUSSCHNEIDEN_H
#define BEFEHLAUSSCHNEIDEN_H

#include <QUndoCommand>
#include <QRect>
#include "BildModell.h"

class Befehlausschneiden: public QUndoCommand
{
public:
    Befehlausschneiden(BildModell* modell, const QRect& rect);

    void undo() override;
    void redo() override;

private:
    QRect rectCutOutImage;
    BildModell* modell = nullptr;
};

#endif // BEFEHLAUSSCHNEIDEN_H
