#include "SobelOperator.h"
#include <QColor>
#include <cmath>

SobelOperator::SobelOperator(const QImage& image)
{
    this->imageWidth = image.width();
    this->imageHeight = image.height();

    for(int i = 0; i < imageWidth; i++)
    {
        for(int j = 0; j < imageHeight; j++)
        {
            QColor Pixel = image.pixelColor(i, j);
            int greyValue = 0.2989 * Pixel.red() + 0.5870 * Pixel.green() + 0.1140 * Pixel.blue();
            this->push_back(greyValue);
        }
    }
}

QImage SobelOperator::applySobel() {
    vector<int> sobelGx = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    vector<int> sobelGy = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    QImage newImage(this->imageWidth, this->imageHeight, QImage::Format_Grayscale8);

    for (int i = 1; i < this->imageWidth - 1; i++) {
        for (int j = 1; j < this->imageHeight - 1 ; j++) {
            int sumGx = 0;
            int sumGy = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    int currentIndex = (i + k) * imageHeight + (j + l);
                    sumGx += this->at(currentIndex) * sobelGx[(k + 1) * 3 + (l + 1)];
                    sumGy += this->at(currentIndex) * sobelGy[(k + 1) * 3 + (l + 1)];
                }
            }

            int pixelValue = sqrt(pow(sumGx, 2) + pow(sumGy, 2));
            pixelValue = qBound(0, pixelValue, 255);

            newImage.setPixel(i, j, qRgb(pixelValue, pixelValue, pixelValue));
        }
    }

    return newImage;
}
