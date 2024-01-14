#include "BildModel.h"
#include "SobelOperator.h"
#include <QErrorMessage>
#include <QFileDialog>
#include <QMessageBox>

namespace
{
constexpr double pi = 3.14159265358979323846;
}

const QImage& BildModel::getImage() const
{
    return image;
}

const QRect& BildModel::getRect() const
{
    return rectImage;
}

int BildModel::getRotationFactor() const
{
    return rotationFactor;
}

int BildModel::getScaleFactor() const
{
    return scaleFactor;
}

void BildModel::setRotationFactor(int rotationFac)
{
    rotationFactor = rotationFac;
}

void BildModel::setScaleFactor(int scaleFac)
{
    scaleFactor = scaleFac;
}

bool BildModel::upload() {
    QString filePath = QFileDialog::getOpenFileName(nullptr, tr("Bild öffnen"), "", tr("Bilder (*.png *.jpg *.jpeg)"));
        if (!filePath.isEmpty())
    {
        ImageInput = QImage(filePath);
        image = ImageInput;
        rectImage = ImageInput.rect();

        emit BildModel::imageChanged();
        return true;
    }
    else{
        QMessageBox::critical(nullptr, tr("Error Loading Image"), tr("An error occurred while loading the image. Please check the selected file and try again."));
    }

    return false;
}

bool BildModel::save() {
    QString filename = QFileDialog::getSaveFileName(nullptr, tr("Bild speichern"), "", tr("Bilder (*.png *.jpg *.jpeg)"));
    if (!filename.isEmpty()) {
        if (image.isNull()) {
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

QPoint BildModel::cornerMinMax() const
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

void BildModel::checkCurrentTransformations()
{

    if (edgeDetektionOn == true)
        this->edgeDetektion();

    else if (isGrayScale == true)
        this->grayscale();
}

void BildModel::affineTransformation()
{
    double rad = rotationFactor * pi/180;
    QTransform transformationMatrix;
    transformationMatrix.setMatrix(scaleFactor * cos(rad), -scaleFactor * sin(rad), 0, scaleFactor * sin(rad),scaleFactor * cos(rad),0,0,0,1);
    rectImage = transformationMatrix.mapRect(ImageInput.rect()); //Transformation der BoundingBox
    rectImage.translate(-1*cornerMinMax()); //translation der Boundingbox in den positiven x und y bereich.
    image = ImageInput.transformed(transformationMatrix); //Transformation des Bildes.
}

void BildModel::performTransformation()
{

    this->affineTransformation();
    this->checkCurrentTransformations();

    emit BildModel::imageChanged();
}
void BildModel::scaleImage(int scale)
{
    this->setScaleFactor(scale);
    performTransformation();
}

void BildModel::rotateImage(int degree)
{
    this->setRotationFactor(degree);
    performTransformation();
}


void BildModel::grayscaleOnOff()
{
    if (isGrayScale == false)
    {
        isGrayScale = true;
        this->performTransformation();
    }

    else
    {
        isGrayScale = false;
        this->performTransformation();
    }
}

void BildModel::grayscale()
{
    image = image.convertToFormat(QImage::Format_Grayscale8);
    emit BildModel::imageChanged();
}

 void BildModel::edgeDetectionOnOff()
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

void BildModel::edgeDetektion()
{

    SobelOperator edgeImage(this->image);
    image = edgeImage.applySobel();
    emit BildModel::imageChanged();
}

void BildModel::resetImage()
{
    image = ImageInput;
    rectImage = ImageInput.rect();
    edgeDetektionOn = false;
    isGrayScale = false;
    emit BildModel::imageChanged();
}

