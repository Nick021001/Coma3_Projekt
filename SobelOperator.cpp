#include "SobelOperator.h"
#include <QColor>

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
