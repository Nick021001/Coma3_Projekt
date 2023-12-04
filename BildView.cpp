#include "BildView.h"
#include "BildModell.h"

#include<QPainter>

BildView::BildView(BildModell& modell, QWidget* parent): QWidget(parent), pmodell(modell)
{
    connect(&modell, &BildModell::posChanged, this, QOverload<>::of(&QWidget::update));
    connect(&modell, &BildModell::pixelSizeChanged, this, QOverload<>::of(&QWidget::update));
    connect(&modell, &BildModell::imageChanged, this, QOverload<>::of(&QWidget::update));
}

void BildView::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(QPoint(), this->pmodell.getImage());
}
