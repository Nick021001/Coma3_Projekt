#ifndef BILDMODELL_H
#define BILDMODELL_H

#include <QImage>
#include <QWidget>
#include <QPoint>
#include <QString>

class BildModell: public QObject{
    Q_OBJECT

public:

    BildModell(QObject* parent ,const QString& file)
        :image(QImage(file)),
        currentMousePosition(QPoint()),
        pixelSize(image.size())
    {}

    void setPos(const QPoint& pos);

    //void setPixelSize(const QSize& size);

    QPoint getPos() const;

    QImage getImage() const;

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
};

#endif // BILDMODELL_H
