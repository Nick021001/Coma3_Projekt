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

void BildModell::grayscale(){
    //Convert QPixmap to QImage for pixelwise transformation
    QImage originalImage = this->image.toImage();
    QImage grayscaleImage(originalImage.size(), QImage::Format_Grayscale8);

    for (int y = 0; y < originalImage.height(); ++y) {
        for (int x = 0; x < originalImage.width(); ++x) {
            QRgb pixel = originalImage.pixel(x, y);
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);
            int gray = static_cast<int>(0.2126 * red + 0.7152 * green + 0.0722 * blue);
            grayscaleImage.setPixel(x, y, gray);
        }
    }

    this->image = QPixmap::fromImage(grayscaleImage); // Convert QImage back to QPixmap
    emit BildModell::imageChanged();

}



bool BildModell::laden() {
    QString filePath = QFileDialog::getOpenFileName(nullptr, tr("Bild öffnen"), "", tr("Bilder (*.png *.jpg *.jpeg)"));
        if (!filePath.isEmpty()) {
        QImage newImage(filePath);
        if (!newImage.isNull()) {
            if (!imageLabel) {
                imageLabel = new QLabel;
                imageLabel->setPixmap(QPixmap::fromImage(newImage));
                imageLabel->show();
            } else {
                imageLabel->setPixmap(QPixmap::fromImage(newImage));
            }
            emit BildModell::imageChanged();
            return true;
        } else {
            qDebug() << "Fehler beim Laden des Bildes: " << filePath;
        }
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
