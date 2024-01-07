#ifndef BILDMODELL_H
#define BILDMODELL_H

#include <QImage>
#include <QWidget>
#include <QPoint>
#include <QRect>
#include <QString>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <QTransform>
#include <QLabel>


class BildModell : public QObject {
    Q_OBJECT

public:
    BildModell(QObject* parent = nullptr, const QString& file = QString())
        : image(file.isEmpty() ? QPixmap() : QPixmap(file)),
        currentMousePosition(QPoint()),
        pixelSize(image.size()),
        rectImage(image.rect()),
        ImageInput(image)
    {
        if (file.isEmpty()) {
            image = QPixmap();
        }
    }

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
    void grayscale();
    bool laden();
    bool speichern();

private:
    QPixmap image;
    QPoint currentMousePosition;
    QSize pixelSize;
    QRect rectImage;
    QTransform transformationMatrix = QTransform();
    QLabel* imageLabel = nullptr;
    const QPixmap ImageInput;
    int scaleFactor = 1;
    int rotationFactor = 0;
};

#endif // BILDMODELL_H
