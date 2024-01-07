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

    void zoomInImage(const QRect& rect);

    const QImage& getImage() const;

    const QRect& getRect() const;

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
    void performTransformation();

signals:
    void imageChanged();

public slots:
    void scaleImage(int scale);
    void rotateImage(int degree);
    void pushImageRotationAfterRelease();
    void pushImageScaleAfterChange(int scale);
    void grayscale();
    void edgeDetektion();
    void resetImage();
    bool laden();
    bool speichern();

private:
    QImage ImageInput;
    QImage image;
    QRect rectImage;

    bool cuttedOut = false;
    bool isGreyScale = false;
    bool edgeDetektionOn = false;

    QTransform transformationMatrix;
    int scaleFactor = 1;
    int rotationFactor = 0;

    QUndoStack* undostack = nullptr;

    QPoint cornerMinMax() const;
    void checkCurrentTransformations();
};

#endif // BILDMODELL_H
