#include "mainwindow.h"

#include <QtWidgets>
#include "wizardscene.h"

MainWindow::MainWindow() {
    createActions();
    createToolBox();
    createMenus();

    scene = new WizardScene(fileMenu, this);
    scene->setSceneRect(QRectF(0, 0, 500, 500));

    QHBoxLayout *layout = new QHBoxLayout;
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("PatWizard"));
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
    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(sceneScaleCombo);
}


void MainWindow::createMenus() {
    // file menu entry
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openFileAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}



void MainWindow::openFile() {
    status->showMessage("OpenFile:: not implemented yet");
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
