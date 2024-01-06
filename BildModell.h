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

    BildModell(QObject* parent, QUndoStack* undostack, const QString& file)
        :ImageInput(QImage(file)),
        image(ImageInput),
        rectImage(image.rect()),
        undostack(undostack)
    {}

    void zoomInImage(const QRect& rect);

    const QImage& getImage() const;

    const QRect& getRect() const;

    inline int getRotationFactor()
    {
        return rotationFactor;
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
    void rotateImageAfterRelease();
    void grayscale();
    void edgeDetektion();
    void resetImage();

private:
    const QImage ImageInput;
    QImage image;
    QRect rectImage;

    bool cuttedOut;
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
