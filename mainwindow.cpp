#include "mainwindow.h"

#include <QtWidgets>
#include <QToolButton>
#include "wizardscene.h"
#include "gr_object.h"
#include "GeometrySolver/gemetrysolver.h"

MainWindow::MainWindow() {
    createActions();
    createToolBar();
    createMenus();
    createToolBox();

    scene = new WizardScene(fileMenu, this);
    scene->setSceneRect(QRectF(0, 0, 500, 500));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);

    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("PatWizard"));
    setUnifiedTitleAndToolBarOnMac(true);

    status = statusBar();
    // Init gemetrySolver. Uncomment once it's implemented.
    //solver = new GemetrySolver();
    // TODO: add hardcode init of objects.
}


void MainWindow::createActions() {
    // action for opening file
    openFileAction = new QAction(tr("&File"), this);
    openFileAction->setShortcuts(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Open PCB file"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    // add action for addConstrain ToolButton.
    toolbarAddConstrAction = new QAction(this);
    toolbarAddConstrAction->setShortcut(tr("Ctrl+A"));
    toolbarAddConstrAction->setCheckable(true);
    toolbarAddConstrAction->setIconText(tr("Hi"));
    connect(toolbarAddConstrAction, SIGNAL(triggered(bool)), this, SLOT(addConstrModeApply(bool)));

    // add action for calcConstrains ToolButton/
    toolbarCalcConstrAction = new QAction(this);
    toolbarCalcConstrAction->setShortcut(tr("Ctrl+C"));
    toolbarCalcConstrAction->setIconText(tr("Calc"));
    connect(toolbarCalcConstrAction, SIGNAL(triggered()), this, SLOT(calculateConstrains()));
}


void MainWindow::createToolBar() {
    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    addConstrButton = new QToolButton;
    addConstrButton->setDefaultAction(toolbarAddConstrAction);

    calcConstrainsButton = new QToolButton;
    calcConstrainsButton->setDefaultAction(toolbarCalcConstrAction);

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(sceneScaleCombo);
    pointerToolbar->addWidget(addConstrButton);
    pointerToolbar->addWidget(calcConstrainsButton);
}


void MainWindow::createMenus() {
    // file menu entry
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openFileAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}



void MainWindow::createToolBox() {
    QGridLayout *layout = new QGridLayout;
    QToolButton *button = new QToolButton;
    button->setDefaultAction(toolbarAddConstrAction);
    layout->addWidget(button);
    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);
    qDebug() << "Oo";
    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(200);
    toolBox->addItem(itemWidget, tr("What?"));
}


void MainWindow::openFile() {
    QString fileName =
            QFileDialog::getOpenFileName(this, tr("Open PCB File"), ".", tr("PCB files(*.pcb)"));
    //fabric = new GrRdrFabricImp<GR>(filename);
    //reader = fabric->create();
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About PatWizard"),
                       tr("<b>PatWizard</b> is the bad example of C++ code."));
}


void MainWindow::sceneScaleChanged(const QString &scale) {
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::addConstrModeApply(bool checked) {
    qDebug() << "hi" << checked;
}

void MainWindow::calculateConstrains()
{
    static bool calcPending = false;
    qDebug() << "calculateConstrains()";
    if (calcPending) {
        qDebug() << "calculation is already pending!";
    }

}
