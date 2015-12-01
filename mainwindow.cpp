#include "mainwindow.h"

#include <QtWidgets>
#include "wizardscene.h"
#include "gr_object.h"

MainWindow::MainWindow() {
    createActions();
    createToolBox();
    createMenus();

    scene = new WizardScene(fileMenu, this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));

    QHBoxLayout *layout = new QHBoxLayout;
    //layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Diagramscene"));
    setUnifiedTitleAndToolBarOnMac(true);

    status = statusBar();
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
}


void MainWindow::createToolBox() {
}


void MainWindow::createMenus() {
    // file menu entry
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openFileAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
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
