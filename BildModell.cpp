#include "BildModell.h"

const QPoint& BildModell::getPos() const
{
    return this->currentMousePosition;
}

void BildModell::setPos(const QPoint& pos)
{
    this->currentMousePosition = pos;
}

const QImage& BildModell::getImage() const
{
    return this->image;
}

const QRect& BildModell::getRecF() const
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

QPoint BildModell::cornerMinMax() const
{
    QPoint topleft = rectImage.topLeft();
    QPoint topright = rectImage.topRight();
    QPoint bottomleft = rectImage.bottomLeft();
    QPoint bottomright = rectImage.bottomRight();

    int xmin;
    int ymin;

    if (topleft.x() < bottomleft.x())
    {
        xmin = topleft.x();
    }
    else
    {
        xmin = bottomleft.x();
    }

    if (topright.y() < bottomright.y())
    {
        ymin = topright.y();
    }
    else
    {
        ymin = bottomright.y();
    }

    return QPoint(xmin, ymin);
}

void BildModell::performTransformation()
{
    const double pi = 3.14159265359;
    double rad = rotationFactor * pi/180;
    transformationMatrix.setMatrix(scaleFactor * cos(rad), -scaleFactor * sin(rad), 0, scaleFactor * sin(rad),scaleFactor * cos(rad),0,0,0,1);
    this->rectImage = transformationMatrix.mapRect(ImageInput.rect());
    this->rectImage.translate(-1*cornerMinMax());

    this->image = ImageInput.transformed(transformationMatrix);

    emit BildModell::imageChanged();
}
void BildModell::scaleImage(int scale)
{
    scaleFactor = scale;
    performTransformation();
}

void BildModell::rotateImage(int degree)
{
    rotationFactor = degree;
    performTransformation();
}

void BildModell::grayscale()
{
    this->image = this->image.convertToFormat(QImage::Format_Grayscale8);
    emit BildModell::imageChanged();
}

void BildModell::edgeDetektion()
{
    SobelOperator edgeImage(this->image);
    this->image = edgeImage.applySobel();
    emit BildModell::imageChanged();
}

