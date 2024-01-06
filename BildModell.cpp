#include "BildModell.h"
#include "SobelOperator.h"
#include "Befehlrotieren.h"

namespace
{
constexpr double pi = 3.14159265358979323846;
}

void BildModell::zoomInImage(const QRect& rect)
{
    rectImage = rect;
    image = image.copy(rect);
    rectImage.moveTo(QPoint());
    cuttedOut = true;
    emit BildModell::imageChanged();
}
const QImage& BildModell::getImage() const
{
    return image;
}

const QRect& BildModell::getRect() const
{
    return rectImage;
}

/*
void BildModell::setMemento(const Memento& memento)
{
    image = memento.image;
    emit BildModell::imageChanged();
}

BildModell::MementoPtr BildModell::getMemento() const
{
    std::unique_ptr<Memento> memento{ new Memento };
    memento->image = image;
    return memento;
}
*/
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
        xmin = topleft.x();

    else
        xmin = bottomleft.x();

    if (topright.y() < bottomright.y())
        ymin = topright.y();

    else
        ymin = bottomright.y();

    return QPoint(xmin, ymin);
}

void BildModell::checkCurrentTransformations()
{

    if (edgeDetektionOn == true)
        this->edgeDetektion();

    else if (isGreyScale == true)
        this->grayscale();
}

void BildModell::performTransformation()
{
    double rad = rotationFactor * pi/180;
    transformationMatrix.setMatrix(scaleFactor * cos(rad), -scaleFactor * sin(rad), 0, scaleFactor * sin(rad),scaleFactor * cos(rad),0,0,0,1);
    rectImage = transformationMatrix.mapRect(ImageInput.rect());
    rectImage.translate(-1*cornerMinMax());
    image = ImageInput.transformed(transformationMatrix);

    this->checkCurrentTransformations();

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

void BildModell::rotateImageAfterRelease()
{
    auto cmd = new Befehlrotieren(this, rotationFactor);
    undostack->push(cmd);
}

void BildModell::grayscale()
{
    image = image.convertToFormat(QImage::Format_Grayscale8);
    isGreyScale = true;
    emit BildModell::imageChanged();
}

void BildModell::edgeDetektion()
{
    SobelOperator edgeImage(this->image);
    image = edgeImage.applySobel();
    edgeDetektionOn = true;
    emit BildModell::imageChanged();
}

void BildModell::resetImage()
{
    image = ImageInput;
    rectImage = ImageInput.rect();
    emit BildModell::imageChanged();
}

