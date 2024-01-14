#ifndef BILDMODEL_H
#define BILDMODEL_H

#include <QImage>
#include <QString>
#include <QRect>
#include <QTransform>
#include <QObject>

class BildModel: public QObject
{
    Q_OBJECT
    QImage ImageInput; //eingeladenes Bild
    QImage image; //aktuelles Bild
    QRect rectImage;

    bool isGrayScale = false; //gibt an ob Grayscale an ist oder nicht
    bool edgeDetektionOn = false; //gibt an ob die Kantenerkennung an ist oder nicht

    int scaleFactor = 1; //aktueller Skalierungsfaktor
    int rotationFactor = 0; //aktueller Rotationsfaktor

    //private Methoden, diese sollen die Rechnungen durchführen um das Bild zu verändern
    QPoint cornerMinMax() const; //berechnet die Translation für die Boundingbox des Biles
    void checkCurrentTransformations(); //checkt ob die nicht affinen Transformationen an sind und führt sie aus
    void affineTransformation(); //berechnet die Affine Transformation des Bildes
    void edgeDetektion(); //berechnet die Kantenerkennung
    void grayscale(); //wandelt das Bild in ein Graustufenbild um

public:

    BildModel(QObject* parent){};

    const QImage& getImage() const;

    const QRect& getRect() const;

    int getRotationFactor() const;

    void setRotationFactor(int rotationFac);

    int getScaleFactor() const;

    void setScaleFactor(int scaleFac);

    void scaleImage(int scale);

    void rotateImage(int degree);

    void resetImage();

    void edgeDetectionOnOff();

    void grayscaleOnOff();

    void performTransformation(); //führt alle Transformationen aus

    bool upload();

    bool save();

signals:
    void imageChanged();
};

#endif // BILDMODEL_H
