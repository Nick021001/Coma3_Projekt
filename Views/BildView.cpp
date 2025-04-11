#include "BildView.h"
#include "BildModel.h"
#include <QPainter>

BildView::BildView(BildModel& model, QWidget* parent): QWidget(parent), pmodel(model)
{
    connect(&model, &BildModel::imageChanged, this, QOverload<>::of(&QWidget::update));
    this->setFocusPolicy(Qt::StrongFocus);
}

void BildView::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawImage(pmodel.getRect(), pmodel.getImage());
}
