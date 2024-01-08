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

    BildModell(QObject* parent, QUndoStack* undostack)
        :undostack(undostack)
    {}

    void cutOutImage(const QRect& rect);

    const QImage& getImage() const;

    const QRect& getRect() const;

    void performTransformation(); //führt alle Transformationen aus


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

    /*
    class Memento
    {
        friend class BildModell;

        QImage image;
        Memento() = default;
    public:
        ~Memento() = default;
    };

    using MementoPtr = std::shared_ptr<Memento>;

    void setMemento(const Memento& memento);
    MementoPtr getMemento() const;
   */

signals:
    void imageChanged();

public slots:
    void scaleImage(int scale);
    void rotateImage(int degree);
    void pushImageRotationAfterRelease();
    void pushImageScaleAfterChange(int scale);
    void resetImage();
    void edgeDetektionOnOff();
    void grayscaleOnOff();
    bool laden();
    bool speichern();

private:
    QImage ImageInput; //eingeladenes Bild
    QImage image; //aktuelles Bild
    QRect rectImage;

    bool cuttedOut = false;
    bool isGreyScale = false;
    bool edgeDetektionOn = false;

    QTransform transformationMatrix;
    int scaleFactor = 1;
    int rotationFactor = 0;

    QUndoStack* undostack = nullptr;

    //private Methoden, diese sollen die Rechnungen durchführen um das Bild zu verändern
    QPoint cornerMinMax() const; //berechnet die Translation für die Boundbox des Biles
    void checkCurrentTransformations(); //checkt ob die nicht affinen Transformationen an sind und führt sie aus
    void affineTransformation(); //berechnet die Affine Transformation des Bildes
    void edgeDetektion(); //berechnet die Kantenerkennung
    void grayscale(); //wandelt das Bild ein Graustufenbild um
};

#endif // BILDMODELL_H
