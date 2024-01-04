#include "Befehlausschneiden.h"

Befehlausschneiden::Befehlausschneiden(BildModell* modell, const QRect& rect)
    :rectCutOutImage(rect)
    ,modell(modell)
{
    setText(QString("Es wurde ein Bild ausgeschnitten"));
}

void Befehlausschneiden::undo()
{
    modell->zoomInImage(rectCutOutImage);
}

void Befehlausschneiden::redo()
{
    modell->zoomInImage(rectCutOutImage);
}
