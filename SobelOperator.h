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

    QImage applySobel();
};

#endif // SOBELOPERATOR_H
