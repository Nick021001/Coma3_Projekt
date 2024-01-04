#ifndef BILDMODELL_H
#define BILDMODELL_H

#include <QImage>
#include <QWidget>
#include <QPointF>
#include <QString>
#include <QRect>
#include <QSize>
#include <QPixmap>
#include <QTransform>

class BildModell: public QObject{
    Q_OBJECT

public:

    BildModell(QObject* parent ,const QString& file)
        :ImageInput(QImage(file)),
        image(ImageInput),
        rectImage(image.rect())
    {}

    void zoomInImage(const QRect& rect);

    const QImage& getImage() const;

    const QRect& getRect() const;

signals:
    void imageChanged();

public slots:
    void scaleImage(int scale);
    void rotateImage(int degree);
    void grayscale();
    void edgeDetektion();
    void resetImage();

private:
    const QImage ImageInput;
    QImage image;
    QRect rectImage;

    QTransform transformationMatrix;
    int scaleFactor = 1;
    int rotationFactor = 0;

    QPoint cornerMinMax() const;
    void performTransformation();
};

#endif // BILDMODELL_H
