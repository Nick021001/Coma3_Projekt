#include "gaussianoperator.h"

GaussianOperator::GaussianOperator(const QImage& image)
{
    imageWidth = image.width();
    imageHeight = image.height();

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

QImage GaussianOperator::applyGaussian(double std)
{

}
