#ifndef BILDVIEW_H
#define BILDVIEW_H

#include <QWidget>

class BildModell;

class BildView: public QWidget
{
   Q_OBJECT

   BildModell& pmodell;

public:
   BildView(BildModell& modell, QWidget *parent = nullptr);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // BILDVIEW_H
