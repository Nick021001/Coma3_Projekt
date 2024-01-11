#include "BildModell.h"
#include "SobelOperator.h"
#include <QErrorMessage>
#include <qdebug.h>
#include <QFileDialog>
#include <QMessageBox>

namespace
{
constexpr double pi = 3.14159265358979323846;
}

const QImage& BildModell::getImage() const
{
    return image;
}

const QRect& BildModell::getRect() const
{
    return rectImage;
}

int BildModell::getRotationFactor() const
{
    return rotationFactor;
}

int BildModell::getScaleFactor() const
{
    return scaleFactor;
}

void BildModell::setRotationFactor(int rotationFac)
{
    rotationFactor = rotationFac;
}

void BildModell::setScaleFactor(int scaleFac)
{
    scaleFactor = scaleFac;
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
        QMessageBox::critical(nullptr, tr("Error Loading Image"), tr("An error occurred while loading the image. Please check the selected file and try again."));
    }

    return false;
}

bool BildModell::speichern() {
    QString filename = QFileDialog::getSaveFileName(nullptr, tr("Bild speichern"), "", tr("Bilder (*.png *.jpg *.jpeg)"));
    if (!filename.isEmpty()) {
        if (image.isNull()) {
            //qDebug() << "Kein Bild zum Speichern vorhanden.";
            QMessageBox::critical(nullptr, tr("Error save Image"), tr("There is no image to save."));
            return false;
        }
        if (!image.save(filename)) {
            QMessageBox::critical(nullptr, tr("Error Saving Image"), tr("An error occurred while saving the image to the file: %1").arg(filename));
            return false;
        }
        QMessageBox::information(nullptr, tr("Image Saved"), tr("The image has been saved successfully."));
        return true;
    } else {
        QMessageBox::information(nullptr, tr("Operation Cancelled"), tr("Saving operation cancelled by the user."));
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
    QTransform transformationMatrix;
    transformationMatrix.setMatrix(scaleFactor * cos(rad), -scaleFactor * sin(rad), 0, scaleFactor * sin(rad),scaleFactor * cos(rad),0,0,0,1);
    rectImage = transformationMatrix.mapRect(ImageInput.rect()); //Transformation der BoundingBox
    rectImage.translate(-1*cornerMinMax()); //translation der Boundingbox in den positiven x und y bereich.
    image = ImageInput.transformed(transformationMatrix); //Transformation des Bildes.
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
    edgeDetektionOn = false;
    isGreyScale = false;
    emit BildModell::imageChanged();
}

