#include "BildModell.h"

QPoint BildModell::getPos() const
{
    return this->currentMousePosition;
}

void BildModell::setPos(const QPoint& pos)
{
    this->currentMousePosition = pos;
}

QPixmap BildModell::getImage() const
{
    return this->image;
}

QRect BildModell::getRecF() const
{
    return this->rectImage;
}


//public slots

void BildModell::zoomIn(QString rectangle)
{
    if (rectangle == "Pixelgröße")
    {
        this->rectImage = QRect(0, 0, ImageInput.width(), ImageInput.height());
        //this->image = image.copy(rectImage);
        this->image = this->ImageInput;
        emit BildModell::imageChanged();
    }
    else if (rectangle == "75x75")
    {
        this->rectImage.setRect(0, 0, 75, 75);
        this->rectImage.moveCenter(this->currentMousePosition);
        this->image = this->image.copy(rectImage);
        emit BildModell::imageChanged();
    }

    else if (rectangle == "150x150")
    {
        this->rectImage.setRect(0, 0, 150, 150);
        this->rectImage.moveCenter(this->currentMousePosition);
        this->image = this->image.copy(rectImage);
        emit BildModell::imageChanged();
    }

    else
    {
        this->rectImage.setRect(0, 0, 250, 250);
        this->rectImage.moveCenter(this->currentMousePosition);
        this->image = this->image.copy(rectImage);
        emit BildModell::imageChanged();
    }
}

void BildModell::scaleImage(int scale)
{
    //this->scaleFactor = scale;
    int width = this->image.width() * scale;
    int height = this->image.height() * scale;

    this->rectImage.setBottomRight(QPoint(width*scale, height*scale));
    this->image = image.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //this->pixelSize = image.size();
    emit BildModell::imageChanged();
}

void BildModell::rotateImage(int degree)
{
    degree = 1;
}
