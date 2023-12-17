#ifndef SOBELOPERATOR_H
#define SOBELOPERATOR_H

#include <QImage>

using ImageArray = std::vector<int>;

class SobelOperator: public ImageArray
{
    int imageWidth;
    int imageHeight;
public:
    SobelOperator(const QImage& image);
};

#endif // SOBELOPERATOR_H
