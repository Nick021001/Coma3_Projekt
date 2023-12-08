#ifndef BILDMODELL_H
#define BILDMODELL_H

#include <QImage>
#include <QWidget>
#include <QPointF>
#include <QString>
#include <QRect>
#include <QSize>
#include <QPixmap>


class BildModell: public QObject{
    Q_OBJECT

public:

    BildModell(QObject* parent ,const QString& file)
        :image(QPixmap(file)),
        currentMousePosition(QPoint()),
        pixelSize(image.size()),
        rectImage(image.rect()),
        ImageInput(image)
    {}

    void setPos(const QPoint& pos);

    QPoint getPos() const;

    QPixmap getImage() const;

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
    QPixmap image;
    QPoint currentMousePosition;
    QSize pixelSize;
    QRect rectImage;
    const QPixmap ImageInput;
    int scaleFactor = 1;
};

#endif // BILDMODELL_H
