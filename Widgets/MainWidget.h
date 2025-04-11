#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>

class BildModel;

class MainWidget : public QMainWindow
{
    Q_OBJECT

    BildModel* bildModel;

public:
    MainWidget();
    ~MainWidget(){};
};

#endif // MAINWIDGET_H
