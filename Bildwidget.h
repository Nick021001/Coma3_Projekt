#ifndef BILDWIDGET_H
#define BILDWIDGET_H

#include <QImage>
#include <QWidget>
#include <QPoint>

class BildWidget: public QWidget{
    QPoint aktulleMausPosition = QPoint(); //wird standardmäßig auf (0, 0) gesetzt
public:
    BildWidget();
    ~BildWidget();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
};

#endif // BILDWIDGET_H
