#ifndef GAUSSIANOPERATOR_H
#define GAUSSIANOPERATOR_H

#include <QImage>

using ImageArray = std::vector<int>;

class GaussianOperator: public ImageArray
{
    int imageWidth;
    int imageHeight;

public:
    GaussianOperator(const QImage& image);

    QImage applyGaussian(double std);
};

#endif // GAUSSIANOPERATOR_H
