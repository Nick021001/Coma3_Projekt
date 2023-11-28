#include "mainwindow.h"

// Qt includes
#include "mainwindow.h"
#include <QDial>
#include <QApplication>
#include <QSlider>
#include <QToolbar>
#include <QComboBox>
#include <QDockWidget>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

//Projekt Includes
#include "Bildwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(500, 500);
    //scale button
    QDoubleSpinBox* scale_button = new QDoubleSpinBox();

    //Rotate Button
    QDial* rotate_button = new QDial();

    //edge detektion
    QPushButton* edge_detektion_button = new QPushButton("edge detektion");

    //Toolbar
    QWidget* toolbar_widget = new QWidget();
    QToolBar* toolbar = new QToolBar(toolbar_widget);
    toolbar->addWidget(scale_button);
    toolbar->addWidget(rotate_button);
    toolbar->addWidget(edge_detektion_button);

    //Pixelgrößen Button
    QComboBox* button_auswahl_pixelgroeße = new QComboBox();
    button_auswahl_pixelgroeße->addItems({"Pixelgröße", "75x75", "150x150", "250x250"});

    //Speicher Button
    QPushButton* speicher_button = new QPushButton("Speichern");

    //Dockwidget
    QWidget* dock_widget_content = new QWidget;
    QWidget* dock_widget = new QWidget;
    QDockWidget* dock = new QDockWidget("right dock", dock_widget);

    dock->setWidget(dock_widget_content);

    QVBoxLayout* layout = new QVBoxLayout(dock_widget_content);
    layout->addWidget(button_auswahl_pixelgroeße);
    layout->addWidget(speicher_button);

    dock_widget_content->setLayout(layout);

    dock->setAllowedAreas(Qt::RightDockWidgetArea);
    //toolbar_widget->addToolBar(toolbar);

    QImage bild = QImage("C:/Users/nikla/OneDrive/Dokumente/5. Semester/Computerorientierte Mathematik 3/Coma3_Projekt/Ronaldihno.jpg");
    QLabel* label = new QLabel;
    label->setPixmap(QPixmap::fromImage(bild));

    resize(2* bild.size());

    addToolBar(toolbar);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    setCentralWidget(label);
}

MainWindow::~MainWindow()
{

}
