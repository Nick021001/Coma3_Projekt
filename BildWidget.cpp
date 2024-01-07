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
#include <QUndoStack>
#include <QUndoView>
#include <QIcon>


BildWidget::BildWidget()
{
    //resize(500, 500);
    //scale button
    QSpinBox* scale_button = new QSpinBox();
    scale_button->setRange(1, 1000);

    //Rotate Button
    QSlider* rotate_slider = new QSlider(Qt::Horizontal);
    rotate_slider->setMinimum(0);
    rotate_slider->setMaximum(360);
    rotate_slider->setFixedWidth(200);

    //winkel Label
    QLabel* winkel_zahl = new QLabel("0");

    //edge detektion
    QPushButton* edge_detektion_button = new QPushButton("edge detektion");

    //convert to greyscale
    QPushButton* grayscale = new QPushButton("Convert to Grayscale");

    //Toolbar
    QToolBar* toolbar = new QToolBar();
    toolbar->addWidget(scale_button);
    toolbar->addWidget(rotate_slider);
    toolbar->addWidget(winkel_zahl);
    toolbar->addWidget(edge_detektion_button);
    toolbar->addWidget(grayscale);

    //Reset Button
    QPushButton* reset_button = new QPushButton();
    QIcon reset_icon(":/icons/reset.jpeg");
    reset_button->setIcon(reset_icon);
    reset_button->setIconSize(QSize(32, 32));

    //Speicher Button
    QPushButton* speicher_button = new QPushButton("save");
    QIcon save_icon(":/icons/save.jpeg");
    speicher_button->setIcon(save_icon);

    QPushButton* laden_button = new QPushButton("Laden");

    QWidget* edgedetection_window = new QWidget();
    QPushButton* edgedetectionoff = new QPushButton("turn edgedetection off",edgedetection_window);

    QWidget* grayscale_window = new QWidget();
    QPushButton* grayscaleoff = new QPushButton("turn grayscale off",grayscale_window);
    connect(grayscale, &QPushButton::clicked, grayscale_window, &QWidget::show);
    //connect(grayscaleoff, &QPushButton::clicked,...)

    //Dockwidget
    QWidget* dock_widget_content = new QWidget;
    //QWidget* dock_widget = new QWidget;
    QDockWidget* dock = new QDockWidget("right dock");//, dock_widget);

    dock->setWidget(dock_widget_content);

    QVBoxLayout* layout = new QVBoxLayout(dock_widget_content);
    layout->addWidget(speicher_button);
    layout->addWidget(reset_button);
    layout->addWidget(laden_button);

    dock_widget_content->setLayout(layout);

    dock->setAllowedAreas(Qt::RightDockWidgetArea);

    QUndoStack* undostack = new QUndoStack;

    bildModell = new BildModell(this, undostack);
    BildView* view = new BildView(*bildModell, this);
    BildController* controller = new BildController(bildModell, undostack ,view, this);

    connect(scale_button, &QSpinBox::valueChanged, bildModell, &BildModell::scaleImage);

    connect(scale_button, &QSpinBox::valueChanged, bildModell, &BildModell::pushImageScaleAfterChange);

    QObject::connect(rotate_slider, &QSlider::valueChanged, bildModell, &BildModell::rotateImage);

    QObject::connect(rotate_slider, &QSlider::valueChanged, winkel_zahl, qOverload<int>(&QLabel::setNum));

    QObject::connect(rotate_slider, &QSlider::valueChanged, bildModell, &BildModell::rotateImage);

    QObject::connect(rotate_slider, &QSlider::sliderReleased, bildModell, &BildModell::pushImageRotationAfterRelease);

    QObject::connect(grayscale, &QPushButton::clicked, bildModell, &BildModell::grayscale);

    QObject::connect(edge_detektion_button, &QPushButton::clicked, bildModell, &BildModell::edgeDetektion);

    QObject::connect(reset_button, &QPushButton::clicked, bildModell, &BildModell::resetImage);

    QObject::connect(laden_button, &QPushButton::clicked, bildModell, &BildModell::laden);

    QObject::connect(speicher_button, &QPushButton::clicked, bildModell, &BildModell::speichern);

    connect(edge_detektion_button, &QPushButton::clicked, edgedetection_window, &QWidget::show);

    //connect(edgedetectionoff, &QPushButton::clicked,bildmodell,&Bildmodell::);

    connect(grayscale, &QPushButton::clicked, grayscale_window, &QWidget::show);
    //connect(grayscaleoff, &QPushButton::clicked,...)

    QAction* undoAction = undostack->createUndoAction(this);
    toolbar->addAction(undoAction);
    toolbar->addAction(undostack->createRedoAction(this));

    QUndoView* undoView = new QUndoView(undostack);
    QDockWidget* undoDW = new QDockWidget("Befehlshistorie");
    undoDW->setWidget(undoView);
    addDockWidget(Qt::RightDockWidgetArea, undoDW);

    //auto label = new QLabel("Test");
    //Widget zusammsensetzung
    this->addToolBar(toolbar);
    this->setCentralWidget(view);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);
}


