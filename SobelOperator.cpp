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
            this->push_back(Pixel.red());
        }
    }
}

QImage SobelOperator::applySobel()
{
    vector<int> sobelGx = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    vector<int> sobelGy = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    QImage newImage(imageWidth, imageHeight, QImage::Format_Grayscale8);

    for (int i = 0; i < this->imageWidth; i++)
    {
        for (int j = 1; j < this->imageHeight - 1; j++)
        {
            int currentIndex = i*imageWidth + j;
            int sumGx = 0;
            int sumGy = 0;
            for (int k = currentIndex; k <= currentIndex + 8; k++)
            {
                sumGx += this->at(k) * sobelGx[k - currentIndex];
                sumGy += this->at(k) * sobelGy[k - currentIndex];

                int PixelValue = sqrt(pow(sumGx, 2) + pow(sumGy, 2));

                newImage.setPixel(i, j, PixelValue);
            }
        }
    }

}
