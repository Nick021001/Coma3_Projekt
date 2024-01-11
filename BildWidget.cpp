#include "BildWidget.h"
#include "BildModell.h"
#include "BildController.h"
#include "BildView.h"
#include "BildWidgetController.h"

// Qt includes
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

    /* Buttons, widget und anderer stuff*/
    //scale spinbox
    QSpinBox* scale_spinbox = new QSpinBox();
    scale_spinbox->setRange(1, 10);

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

    //Help Button
    QPushButton* help_button = new QPushButton();
    QIcon help_icon(":/icons/help.jpeg");
    help_button->setIcon(help_icon);
    help_button->setIconSize(QSize(32, 32));

    QWidget* help_window = new QWidget();
    help_window->setMinimumSize(500,500);
    help_window->setWindowTitle("?Help?");
    QVBoxLayout* helplayout = new QVBoxLayout(help_window);
    QLabel* help_text1 = new QLabel("Hello, if you need help,<br>please take a look on the user documentation<br>or ask one of the groupmembers for advice!<br>Have fun :)");
    QLabel* help_text2 = new QLabel("Here are some keys you might want to use:");

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(new QLabel("[+][-]"), 0, 0);
    gridLayout->addWidget(new QLabel(": scale"), 0, 1);
    gridLayout->addWidget(new QLabel("[\u2192] and [\u2190]"), 1, 0);
    gridLayout->addWidget(new QLabel(": rotate 90 degrees"), 1, 1);
    gridLayout->addWidget(new QLabel("[\u2191] and [\u2193]"), 2, 0);
    gridLayout->addWidget(new QLabel(": rotate 180 degrees"), 2, 1);
    gridLayout->addWidget(new QLabel("[g]"), 3, 0);
    gridLayout->addWidget(new QLabel(": grayscale on/off"), 3, 1);
    gridLayout->addWidget(new QLabel("[e]"), 4, 0);
    gridLayout->addWidget(new QLabel(": edgedetection on/off"), 4, 1);
    gridLayout->addWidget(new QLabel("backspace/delete [\u2190]"), 5, 0);
    gridLayout->addWidget(new QLabel(": reset"), 5, 1);
    gridLayout->addWidget(new QLabel("return/enter [\u23CE]"), 6, 0);
    gridLayout->addWidget(new QLabel(": save"), 6, 1);

    helplayout->addWidget(help_text1);
    helplayout->addWidget(help_text2);
    helplayout->addLayout(gridLayout);

    //Toolbar
    QToolBar* toolbar = new QToolBar();
    toolbar->addWidget(scale_spinbox);
    toolbar->addWidget(rotate_slider);
    toolbar->addWidget(degree);
    toolbar->addWidget(edge_detektion_button);
    toolbar->addWidget(grayscale);
    toolbar->addWidget(help_button);


    /* Buttons für das user board*/
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

    /*MVC klassen*/

    QUndoStack* undostack = new QUndoStack;

    bildModell = new BildModell(this);
    BildView* view = new BildView(*bildModell, this);
    BildController* controller = new BildController(bildModell, undostack ,view, this);
    Bildwidgetcontroller* bildwidgetcontroller = new Bildwidgetcontroller(bildModell, undostack, view, this);

    connect(scale_spinbox, &QSpinBox::valueChanged, bildwidgetcontroller, &Bildwidgetcontroller::pushScaleafterChange);

    connect(rotate_slider, &QSlider::valueChanged, bildwidgetcontroller, &Bildwidgetcontroller::pushRotationAfterRealse);

    connect(rotate_slider, &QSlider::valueChanged, degree, qOverload<int>(&QLabel::setNum));

    connect(grayscale, &QPushButton::clicked, bildModell, &BildModell::grayscaleOnOff);

    connect(edge_detektion_button, &QPushButton::clicked, bildModell, &BildModell::edgeDetektionOnOff);

    connect(reset_button, &QPushButton::clicked, bildModell, &BildModell::resetImage);

    connect(upload_button, &QPushButton::clicked, bildModell, &BildModell::laden);

    connect(save_button, &QPushButton::clicked, bildModell, &BildModell::speichern);

    connect(help_button, &QPushButton::clicked, help_window, &QWidget::show);

    /* Undo und Redo action*/
    QAction* undoAction = undostack->createUndoAction(this);
    toolbar->addAction(undoAction);
    toolbar->addAction(undostack->createRedoAction(this));

    /* Command history view */
    QUndoView* undoView = new QUndoView(undostack);
    QDockWidget* undoDW = new QDockWidget("Command history");
    undoDW->setWidget(undoView);
    addDockWidget(Qt::RightDockWidgetArea, undoDW);

    view->setFixedSize(1400, 1400);
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(view);
    scrollArea->setWidgetResizable(true);

    //Widget zusammsensetzung
    this->addToolBar(toolbar);
    this->setCentralWidget(scrollArea);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);
}


