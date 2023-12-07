#ifndef BILDMODELL_H
#define BILDMODELL_H

#include <QImage>
#include <QWidget>
#include <QPointF>
#include <QString>
#include <QRectF>
#include <QSize>

class BildModell: public QObject{
    Q_OBJECT

public:

    BildModell(QObject* parent ,const QString& file)
        :image(QImage(file)),
        currentMousePosition(QPoint()),
        pixelSize(image.size()),
        rectImage(0, 0, pixelSize.width(), pixelSize.height())
    {}

    void setPos(const QPoint& pos);

    //void setPixelSize(const QSize& size);

    QPoint getPos() const;

    QImage getImage() const;

    QRectF getRecF() const;

signals:
    void posChanged();
    void pixelSizeChanged();
    void imageChanged();

public slots:
    void scaleImage(int scale);
    void rotateImage(int degree);

private:
    QImage image;
    QPoint currentMousePosition;
    QSize pixelSize;
    QRectF rectImage;
};

#endif // BILDMODELL_H
