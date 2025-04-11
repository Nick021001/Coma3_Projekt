#include "MainWidget.h"
#include "BildModel.h"
#include "BildController.h"
#include "BildView.h"
#include "MainWidgetController.h"

// Qt includes
#include <QSlider>
#include <QToolBar>
#include <QComboBox>
#include <QDockWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QObject>
#include <QUndoStack>
#include <QUndoView>
#include <QIcon>
#include <QScrollArea>
#include <QWidget>


MainWidget::MainWidget()
{
    //resize(500, 500);

    /* Buttons, widget und anderer stuff*/
    //scale spinbox
    QSpinBox* scale_spinbox = new QSpinBox();
    scale_spinbox->setRange(1, 6);

    //Rotate Button
    QSlider* rotate_slider = new QSlider(Qt::Horizontal);
    rotate_slider->setMinimum(0);
    rotate_slider->setMaximum(360);
    rotate_slider->setFixedWidth(200);

    //winkel Label
    QLabel* degree = new QLabel("0");

    //edge detektion
    QPushButton* edge_detection_button = new QPushButton("Edge Detection");

    //convert to greyscale
    QPushButton* grayscale_button = new QPushButton("Convert to Grayscale");

    /* Buttons für das user board*/
    //Reset Button
    QPushButton* reset_button = new QPushButton();
    QIcon reset_icon(":/icons/reset.jpeg");
    reset_button->setIcon(reset_icon);
    reset_button->setIconSize(QSize(32, 32));

    //Toolbar
    QToolBar* toolbar = new QToolBar();
    toolbar->setStyleSheet("QToolBar { background-color: #2E2E2E; }");
    toolbar->addWidget(scale_spinbox);
    toolbar->addWidget(rotate_slider);
    toolbar->addWidget(degree);
    toolbar->addWidget(edge_detection_button);
    toolbar->addWidget(grayscale_button);
    toolbar->addWidget(reset_button);

    //Help Button
    QPushButton* help_button = new QPushButton();
    QIcon help_icon(":/icons/help.jpeg");
    help_button->setIcon(help_icon);
    help_button->setIconSize(QSize(32, 32));

    //Help window
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

    //Speicher Button
    QPushButton* save_button = new QPushButton("Save");
    QIcon save_icon(":/icons/save.jpeg");
    save_button->setIcon(save_icon);

    //Laden Button
    QPushButton* upload_button = new QPushButton("Upload");
    QIcon upload_icon(":/icons/upload.jpeg");
    upload_button->setIcon(upload_icon);

    //Dockwidget
    QWidget* dock_widget_content = new QWidget;
    //QWidget* dock_widget = new QWidget;
    QDockWidget* dock = new QDockWidget("User board");//, dock_widget);

    dock->setWidget(dock_widget_content);

    QVBoxLayout* layout = new QVBoxLayout(dock_widget_content);
    layout->addWidget(upload_button);
    layout->addWidget(save_button);
    layout->addWidget(help_button);

    dock_widget_content->setLayout(layout);

    dock->setAllowedAreas(Qt::RightDockWidgetArea);

    /*MVC klassen*/

    QUndoStack* undostack = new QUndoStack;

    bildModel = new BildModel(this);
    BildView* view = new BildView(*bildModel, this);
    BildController* controller = new BildController(bildModel, undostack ,view, this);
    Mainwidgetcontroller* mainwidgetcontroller = new Mainwidgetcontroller(bildModel, undostack, view, this);

    connect(scale_spinbox, &QSpinBox::valueChanged, mainwidgetcontroller, &Mainwidgetcontroller::pushScaleAfterChange);

    connect(rotate_slider, &QSlider::valueChanged, mainwidgetcontroller, &Mainwidgetcontroller::pushRotationAfterRelease);

    connect(grayscale_button, &QPushButton::clicked, mainwidgetcontroller, &Mainwidgetcontroller::setGreyScaleOnOff);

    connect(edge_detection_button, &QPushButton::clicked, mainwidgetcontroller, &Mainwidgetcontroller::setEdgeDetectionOnOff);

    connect(reset_button, &QPushButton::clicked, mainwidgetcontroller, &Mainwidgetcontroller::setResetImage);

    connect(rotate_slider, &QSlider::valueChanged, degree, qOverload<int>(&QLabel::setNum));

    connect(upload_button, &QPushButton::clicked, mainwidgetcontroller, &Mainwidgetcontroller::uploadImage);

    connect(save_button, &QPushButton::clicked,  mainwidgetcontroller, &Mainwidgetcontroller::saveImage);

    connect(help_button, &QPushButton::clicked, help_window, &QWidget::show);

    /* Undo und Redo action*/
    QAction* undoAction = undostack->createUndoAction(this);
    QAction* redoAction = undostack->createRedoAction(this);
    QIcon undo_icon(":/icons/undo.jpeg");
    undoAction->setIcon(undo_icon);
    QIcon redo_icon(":/icons/redo.png");
    redoAction->setIcon(redo_icon);
    toolbar->addAction(undoAction);
    toolbar->addAction(redoAction);

    /* Befehlshistorie */
    QUndoView* undoView = new QUndoView(undostack);
    QDockWidget* undoDW = new QDockWidget("Command history");
    undoDW->setWidget(undoView);
    addDockWidget(Qt::RightDockWidgetArea, undoDW);

    view->setFixedSize(1600, 1600);
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(view);
    scrollArea->setWidgetResizable(true);

    //Widget zusammsensetzung
    this->addToolBar(toolbar);
    this->setCentralWidget(scrollArea);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);
}


