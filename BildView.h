#ifndef BILDVIEW_H
#define BILDVIEW_H

#include <QWidget>

class BildModel;

class BildView: public QWidget
{
   Q_OBJECT

   BildModel& pmodel;

public:
   BildView(BildModel& model, QWidget *parent = nullptr);
    ~BildView(){}

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // BILDVIEW_H
