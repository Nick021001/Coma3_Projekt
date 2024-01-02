#include "BildView.h"
#include "BildModell.h"

#include <QRectF>
#include <QPainter>

BildView::BildView(BildModell& modell, QWidget* parent): QWidget(parent), pmodell(modell)
{
    connect(&modell, &BildModell::imageChanged, this, QOverload<>::of(&QWidget::update));
}

void BildView::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(this->pmodell.getRect(), this->pmodell.getImage());
}
