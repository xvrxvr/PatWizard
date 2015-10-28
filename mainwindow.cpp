#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Initialized!");
    ui->mainToolBar->setVisible(false);

    createActions();
    createMenus();
}


void MainWindow::createActions() {
    // action for opening file
    openFileAction = new QAction(tr("&Open"), this);
    openFileAction->setShortcuts(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Open PCB file"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFile()));
}


void MainWindow::createMenus() {
    // file menu entry
    fileMenu = ui->menuBar->addMenu(tr("&File"));
    fileMenu->addAction(openFileAction);
}


void MainWindow::openFile() {
    ui->statusBar->showMessage("openFile() not implemented yet!");
}

MainWindow::~MainWindow()
{
    delete ui;
}
