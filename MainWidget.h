#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMainWindow>

class BildModell;

class MainWidget : public QMainWindow
{
    Q_OBJECT

    BildModell* bildModell;

public:
    MainWidget();
    ~MainWidget(){};
};

#endif // MAINWIDGET_H
