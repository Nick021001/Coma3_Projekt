#ifndef BILDMODELL_H
#define BILDMODELL_H

#include <QImage>
#include <QWidget>
#include <QPointF>
#include <QString>
#include <QRect>
#include <QSize>
#include <QTransform>
#include <QUndoStack>

class BildModell: public QObject{
    Q_OBJECT

public:

    BildModell(QObject* parent){};

    const QImage& getImage() const;

    const QRect& getRect() const;


    // inline methods
    inline int getRotationFactor()
    {
        return rotationFactor;
    }

    inline void setRotationFactor(int rotationFac)
    {
        rotationFactor = rotationFac;
    }

    inline int getScaleFactor()
    {
        return scaleFactor;
    }

    inline void setScaleFactor(int scaleFac)
    {
        scaleFactor = scaleFac;
    }

    void performTransformation(); //führt alle Transformationen aus

signals:
    void imageChanged();

public slots:
    void scaleImage(int scale);
    void rotateImage(int degree);
    void resetImage();
    void edgeDetektionOnOff();
    void grayscaleOnOff();
    bool laden();
    bool speichern();

private:
    QImage ImageInput; //eingeladenes Bild
    QImage image; //aktuelles Bild
    QRect rectImage;

    bool isGreyScale = false; //gibt an ob Greyscale an ist oder nicht
    bool edgeDetektionOn = false; //gibt an ob die Kantenerkennung an ist oder nicht

    QTransform transformationMatrix;
    int scaleFactor = 1; //aktueller Skalierungsfaktor
    int rotationFactor = 0; //aktueller Rotationsfaktor

    //private Methoden, diese sollen die Rechnungen durchführen um das Bild zu verändern
    QPoint cornerMinMax() const; //berechnet die Translation für die Boundbox des Biles
    void checkCurrentTransformations(); //checkt ob die nicht affinen Transformationen an sind und führt sie aus
    void affineTransformation(); //berechnet die Affine Transformation des Bildes
    void edgeDetektion(); //berechnet die Kantenerkennung
    void grayscale(); //wandelt das Bild ein Graustufenbild um
};

#endif // BILDMODELL_H
