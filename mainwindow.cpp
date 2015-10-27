#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Initialized!");

    //NOTE: when there will be more menu entries (and more actions),
    // it is recommended to refactor the code below
    // and extract menu creation to another method like createMenus().Now it's left "as is" to show the flow.
    fileMenu = ui->menuBar->addMenu(tr("&File"));

    openFileAction = new QAction(tr("&Open"), this);
    openFileAction->setShortcuts(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Open PCB file"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
    fileMenu->addAction(openFileAction);
}

void MainWindow::openFile() {
    ui->statusBar->showMessage("openFile() not implemented yet!");
}

MainWindow::~MainWindow()
{
    delete ui;
}
