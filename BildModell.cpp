#include "BildModell.h"

QPoint BildModell::getPos() const
{
    return this->currentMousePosition;
}

void BildModell::setPos(const QPoint& pos)
{
    this->currentMousePosition = pos;
}

QImage BildModell::getImage() const
{
    return this->image;
}

QRectF BildModell::getRecF() const
{
    return this->rectImage;
}

void BildModell::scaleImage(int scale)
{
    int width = this->pixelSize.width() * scale;
    int height = this->pixelSize.width() * scale;

    this->rectImage.setBottomRight(QPointF(width*scale, height*scale));
    this->image = image.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //this->pixelSize = image.size();
    emit BildModell::imageChanged();
}

void BildModell::rotateImage(int degree)
{
    degree = 1;
}
