#include "BildView.h"
#include "BildModell.h"

#include <QRectF>
#include <QPainter>

BildView::BildView(BildModell& modell, QWidget* parent): QWidget(parent), pmodell(modell)
{
    connect(&modell, &BildModell::posChanged, this, QOverload<>::of(&QWidget::update));
    connect(&modell, &BildModell::pixelSizeChanged, this, QOverload<>::of(&QWidget::update));
    connect(&modell, &BildModell::imageChanged, this, QOverload<>::of(&QWidget::update));
}

void BildView::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(this->pmodell.getRecF(), this->pmodell.getImage());
}
