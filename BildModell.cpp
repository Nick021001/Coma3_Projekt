#include "BildModell.h"

const QPoint& BildModell::getPos() const
{
    return this->currentMousePosition;
}

void BildModell::setPos(const QPoint& pos)
{
    this->currentMousePosition = pos;
}

void BildModell::zoomInImage(const QRect& rect, const QPoint& translation)
{
    QTransform translatonMatrix = QTransform(1, 0, 0, 1, translation.x(), translation.y());
    this->rectImage = rect;
    this->image = image.copy(this->rectImage);
    this->image = image.transformed(translatonMatrix);
    this->rectImage.moveTo(QPoint());
    emit BildModell::imageChanged();
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

void BildModell::resetImage()
{
    this->image = this->ImageInput;
    this->rectImage = ImageInput.rect();
    emit BildModell::imageChanged();
}

