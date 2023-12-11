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
    int width = this->image.width() / this->scaleFactor * scale;
    int height = this->image.height() / this->scaleFactor * scale;

    this->rectImage.setBottomRight(QPoint(width, height));
    this->image = image.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    this->scaleFactor = scale;
    //this->pixelSize = image.size();
    emit BildModell::imageChanged();
}

void BildModell::rotateImage(int degree)
{
    //if (rotationFactor != 0)
    //{
        //QTransform invertedMatrix = this->transformationMatrix.inverted();
        //this->image = image.transformed(invertedMatrix);
        //this->transformationMatrix.reset();
    //}
    int rotationChanged = this->rotationFactor - degree;
    this->transformationMatrix = transformationMatrix.rotate(rotationChanged);

    this->image = image.transformed(transformationMatrix);

    QPoint bottomRightPoint(this->ImageInput.width(), this->ImageInput.height());
    QPoint bottomRightPointTransformed = transformationMatrix.map(bottomRightPoint);

    this->rectImage.setBottomRight(bottomRightPointTransformed);
    this->rectImage.setTopLeft(QPoint(0, 0));

    this->rotationFactor = degree;

    emit BildModell::imageChanged();

}
