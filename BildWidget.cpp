#include "BildWidget.h"
#include "BildModell.h"
#include "BildController.h"
#include "BildView.h"

// Qt includes
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
#include <QMenuBar>
#include <QSpinBox>
#include <QObject>


BildWidget::BildWidget()
{
    //resize(500, 500);
    //scale button
    QSpinBox* scale_button = new QSpinBox();
    scale_button->setRange(1, 1000);

    //Rotate Button
    QDial* rotate_button = new QDial();

    //edge detektion
    QPushButton* edge_detektion_button = new QPushButton("edge detektion");

    //Toolbar
    QToolBar* toolbar = new QToolBar();
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
    //QWidget* dock_widget = new QWidget;
    QDockWidget* dock = new QDockWidget("right dock");//, dock_widget);

    dock->setWidget(dock_widget_content);

    QVBoxLayout* layout = new QVBoxLayout(dock_widget_content);
    layout->addWidget(button_auswahl_pixelgroeße);
    layout->addWidget(speicher_button);

    dock_widget_content->setLayout(layout);

    dock->setAllowedAreas(Qt::RightDockWidgetArea);

    bildModell = new BildModell(this, "C:/Users/nikla/OneDrive/Dokumente/5. Semester/Computerorientierte Mathematik 3/Coma3_Projekt/Nike Fußball.jpg");
    BildView* view = new BildView(*bildModell, this);
    //BildController* controller = new BildController(bildModell, view, this);

    QObject::connect(scale_button, &QSpinBox::valueChanged, bildModell, &BildModell::scaleImage);

    //auto label = new QLabel("Test");
    //Widget zusammsensetzung
    this->addToolBar(toolbar);
    this->setCentralWidget(view);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);
}


