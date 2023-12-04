#ifndef BILDWIDGET_H
#define BILDWIDGET_H

#include <QWidget>
#include <QMainWindow>

class BildModell;

class BildWidget : public QMainWindow
{
    Q_OBJECT

    BildModell* bildModell;

public:
    BildWidget();
    ~BildWidget(){};
};

#endif // BILDWIDGET_H
