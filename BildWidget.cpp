#include "BildWidget.h"
#include "BildModell.h"
#include "BildController.h"
#include "BildView.h"
#include "BildWidgetController.h"

#include"Befehlrotieren.h"

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
#include <QUndoStack>
#include <QUndoView>
#include <QIcon>
#include <QScrollArea>


BildWidget::BildWidget()
{
    //resize(500, 500);
    //scale button
    QSpinBox* scale_spinbox = new QSpinBox();
    scale_spinbox->setRange(1, 1000);

    //Rotate Button
    QSlider* rotate_slider = new QSlider(Qt::Horizontal);
    rotate_slider->setMinimum(0);
    rotate_slider->setMaximum(360);
    rotate_slider->setFixedWidth(200);

    //winkel Label
    QLabel* degree = new QLabel("0");

    //edge detektion
    QPushButton* edge_detektion_button = new QPushButton("edge detektion");

    //convert to greyscale
    QPushButton* grayscale = new QPushButton("Convert to Grayscale");

    //Toolbar
    QToolBar* toolbar = new QToolBar();
    toolbar->addWidget(scale_spinbox);
    toolbar->addWidget(rotate_slider);
    toolbar->addWidget(degree);
    toolbar->addWidget(edge_detektion_button);
    toolbar->addWidget(grayscale);

    //Reset Button
    QPushButton* reset_button = new QPushButton();
    QIcon reset_icon(":/icons/reset.jpeg");
    reset_button->setIcon(reset_icon);
    reset_button->setIconSize(QSize(32, 32));

    //Speicher Button
    QPushButton* save_button = new QPushButton("save");
    QIcon save_icon(":/icons/save.jpeg");
    save_button->setIcon(save_icon);

    QPushButton* upload_button = new QPushButton("upload");

    //Dockwidget
    QWidget* dock_widget_content = new QWidget;
    //QWidget* dock_widget = new QWidget;
    QDockWidget* dock = new QDockWidget("user board");//, dock_widget);

    dock->setWidget(dock_widget_content);

    QVBoxLayout* layout = new QVBoxLayout(dock_widget_content);
    layout->addWidget(save_button);
    layout->addWidget(reset_button);
    layout->addWidget(upload_button);

    dock_widget_content->setLayout(layout);

    dock->setAllowedAreas(Qt::RightDockWidgetArea);

    QUndoStack* undostack = new QUndoStack;

    bildModell = new BildModell(this);
    BildView* view = new BildView(*bildModell, this);
    BildController* controller = new BildController(bildModell, undostack ,view, this);
    Bildwidgetcontroller* bildwidgetcontroller = new Bildwidgetcontroller(bildModell, undostack, view, this);

    //connect(scale_spinbox, &QSpinBox::valueChanged, bildModell, &BildModell::scaleImage);

    connect(scale_spinbox, &QSpinBox::valueChanged, bildwidgetcontroller, &Bildwidgetcontroller::pushScaleafterChange);

    connect(rotate_slider, &QSlider::valueChanged, bildwidgetcontroller, &Bildwidgetcontroller::pushRotationAfterRealse); //&BildModell::rotateImage);

    connect(rotate_slider, &QSlider::valueChanged, degree, qOverload<int>(&QLabel::setNum));

   // connect(rotate_slider, &QSlider::sliderReleased, bildwidgetcontroller, &Bildwidgetcontroller::pushRotationAfterRealse);

    connect(grayscale, &QPushButton::clicked, bildModell, &BildModell::grayscaleOnOff);

    connect(edge_detektion_button, &QPushButton::clicked, bildModell, &BildModell::edgeDetektionOnOff);

    connect(reset_button, &QPushButton::clicked, bildModell, &BildModell::resetImage);

    connect(upload_button, &QPushButton::clicked, bildModell, &BildModell::laden);

    connect(save_button, &QPushButton::clicked, bildModell, &BildModell::speichern);

    QAction* undoAction = undostack->createUndoAction(this);
    toolbar->addAction(undoAction);
    toolbar->addAction(undostack->createRedoAction(this));

    QUndoView* undoView = new QUndoView(undostack);
    QDockWidget* undoDW = new QDockWidget("Befehlshistorie");
    undoDW->setWidget(undoView);
    addDockWidget(Qt::RightDockWidgetArea, undoDW);

    view->setFixedSize(1400, 1400);
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(view);
    scrollArea->setWidgetResizable(true);

    //auto label = new QLabel("Test");
    //Widget zusammsensetzung
    this->addToolBar(toolbar);
    //this->setCentralWidget(view);
    this->setCentralWidget(scrollArea);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);
}


