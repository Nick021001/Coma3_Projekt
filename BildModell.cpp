#include "BildModell.h"
#include "SobelOperator.h"
#include <QErrorMessage>
#include <qdebug.h>
#include <QFileDialog>

namespace
{
constexpr double pi = 3.14159265358979323846;
}

void BildModell::cutOutImage(const QRect& rect)
{
    rectImage = rect;
    image = image.copy(rect);
    rectImage.moveTo(QPoint());
    cuttedOut = true;
    cutOutArea = rect;
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

bool BildModell::laden() {
    QString filePath = QFileDialog::getOpenFileName(nullptr, tr("Bild öffnen"), "", tr("Bilder (*.png *.jpg *.jpeg)"));
        if (!filePath.isEmpty())
    {
        ImageInput = QImage(filePath);
        image = ImageInput;
        rectImage = ImageInput.rect();

        emit BildModell::imageChanged();
        return true;
    }
    else{
        qDebug() << "Fehler beim Laden des Bildes: " << filePath;
    }

    return false;
}

bool BildModell::speichern() {
    QString filename = QFileDialog::getSaveFileName(nullptr, tr("Bild speichern"), "", tr("Bilder (*.png *.jpg *.jpeg)"));
    if (!filename.isEmpty()) {
        if (image.isNull()) {
            qDebug() << "Kein Bild zum Speichern vorhanden.";
            return false;
        }
        if (!image.save(filename)) {
            qDebug() << "Fehler beim Speichern des Bildes:" << filename;
            return false;
        }
        qDebug() << "Bild erfolgreich gespeichert unter: " << filename;
        return true;
    } else {
        qDebug() << "Speichern vom Benutzer abgebrochen.";
        return false;
    }
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

void BildModell::affineTransformation()
{
    double rad = rotationFactor * pi/180;
    transformationMatrix.setMatrix(scaleFactor * cos(rad), -scaleFactor * sin(rad), 0, scaleFactor * sin(rad),scaleFactor * cos(rad),0,0,0,1);
    rectImage = transformationMatrix.mapRect(ImageInput.rect());
    rectImage.translate(-1*cornerMinMax());
    image = ImageInput.transformed(transformationMatrix);
}

void BildModell::performTransformation()
{

    this->affineTransformation();
    this->checkCurrentTransformations();

    emit BildModell::imageChanged();
}
void BildModell::scaleImage(int scale)
{
    this->setScaleFactor(scale);
    performTransformation();
}

void BildModell::rotateImage(int degree)
{
    this->setRotationFactor(degree);
    performTransformation();
}


void BildModell::grayscaleOnOff()
{
    if (isGreyScale == false)
    {
        isGreyScale = true;
        this->performTransformation();
    }

    else
    {
        isGreyScale = false;
        this->performTransformation();
    }
}

void BildModell::grayscale()
{
    image = image.convertToFormat(QImage::Format_Grayscale8);
    emit BildModell::imageChanged();
}

 void BildModell::edgeDetektionOnOff()
{
    if (edgeDetektionOn == false)
    {
       edgeDetektionOn = true;
       this->performTransformation();
    }

    else
    {
       edgeDetektionOn = false;
       this->performTransformation();
    }
}


void BildModell::edgeDetektion()
{

    SobelOperator edgeImage(this->image);
    image = edgeImage.applySobel();
    emit BildModell::imageChanged();
}

void BildModell::resetImage()
{
    image = ImageInput;
    rectImage = ImageInput.rect();
    cuttedOut = false;
    edgeDetektionOn = false;
    isGreyScale = false;
    emit BildModell::imageChanged();
}

