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
        :image(QImage(file)),
        currentMousePosition(QPoint()),
        pixelSize(image.size()),
        rectImage(image.rect()),
        ImageInput(image)
    {}

    void setPos(const QPoint& pos);

    QPoint getPos() const;

    QImage getImage() const;

    QRect getRecF() const;

signals:
    void posChanged();
    void pixelSizeChanged();
    void imageChanged();

public slots:
    void scaleImage(int scale);
    void rotateImage(int degree);
    void zoomIn(QString rectangle);

private:
    QImage image;
    QPoint currentMousePosition;
    QSize pixelSize;
    QRect rectImage;
    QTransform transformationMatrix = QTransform();
    const QImage ImageInput;
    int scaleFactor = 1;
    int rotationFactor = 0;
};

#endif // BILDMODELL_H
