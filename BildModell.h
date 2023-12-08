#ifndef BILDMODELL_H
#define BILDMODELL_H

#include <QImage>
#include <QWidget>
#include <QPointF>
#include <QString>
#include <QRectF>
#include <QSize>
#include <QPixmap>


class BildModell: public QObject{
    Q_OBJECT

public:

    BildModell(QObject* parent ,const QString& file)
        :image(QPixmap(file)),
        currentMousePosition(QPoint()),
        pixelSize(image.size()),
        rectImage(0, 0, pixelSize.width(), pixelSize.height())
    {}

    void setPos(const QPoint& pos);

    QPoint getPos() const;

    QPixmap getImage() const;

    QRectF getRecF() const;

signals:
    void posChanged();
    void pixelSizeChanged();
    void imageChanged();

public slots:
    void scaleImage(int scale);
    void rotateImage(int degree);
    void zoomIn(QString rectangle);

private:
    QPixmap image;
    QPoint currentMousePosition;
    QSize pixelSize;
    QRectF rectImage;
};

#endif // BILDMODELL_H
