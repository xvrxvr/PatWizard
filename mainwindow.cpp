#include "mainwindow.h"

#include <QtWidgets>
#include <QToolButton>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QMessageBox>
#include <QThread>
#include "wizardscene.h"
#include "gr_object.h"
//#include "GeometrySolver/gemetrysolver.h"

MainWindow::MainWindow() {
    createActions();
    createToolBar();
    createMenus();
    createToolBox();

    userMode = usualMode;

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

    calcPending = false;
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
    toolbarAddConstrAction->setIconText(tr("AddConstrMode"));
    connect(toolbarAddConstrAction, SIGNAL(triggered(bool)), this, SLOT(applyAddConstrMode(bool)));

    // add action for calcConstrains ToolButton/
    toolbarCalcConstrAction = new QAction(this);
    toolbarCalcConstrAction->setShortcut(tr("Ctrl+C"));
    toolbarCalcConstrAction->setIconText(tr("Calc"));
    connect(toolbarCalcConstrAction, SIGNAL(triggered()), this, SLOT(calculateConstrains()));

    // add action for toolbox button "Add Constrain"
    tboxAddConstrainAction = new QAction(this);
    tboxAddConstrainAction->setIconText(tr("Add Constrain"));
    connect(tboxAddConstrainAction, SIGNAL(triggered()), this, SLOT(addConstrain()));
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
    button->setDefaultAction(tboxAddConstrainAction);
    layout->addWidget(button);
    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(200);
    toolBox->addItem(itemWidget, tr("Constrain Addition"));
}

/********************
 * SLOTS impl. section
 *******************/

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

void MainWindow::applyAddConstrMode(bool checked) {
    qDebug() << "applyAddConstrMode::" << checked;
    if (checked) {
        userMode = addConstrainMode;
    } else {
        userMode = usualMode;
    }
    //drawCircuit(); // <-- here? really?
}

void MainWindow::calculateConstrains()
{
    qDebug() << "calculateConstrains()";
    if (calcPending) {
        qDebug() << "calculation is already pending!";
        QMessageBox msgBox;
        msgBox.setText("Calculation is already pending!");
        msgBox.exec();
        return;
    }
    //commented due to incomplete implementation of GemetrySolver.
    //uncomment once it's implemented and tested.
    //QFuture<bool> future = QConcurrent::run(solver->RunSolver, objects);
    //QObject::connect(calculationWatcher, SIGNAL(finished()), this, SLOT(calcFinished()));
    //watcher.setFuture(future);
    calcPending = true;
    QFuture<bool> future = QtConcurrent::run(sleepy);
    connect(&calculationWatcher, SIGNAL(finished()), this, SLOT(calcFinished()));
    calculationWatcher.setFuture(future);
}

void MainWindow::calcFinished() {
    qDebug() << "calc finished";
    bool result = calculationWatcher.future().result();
    qDebug() << "result is " << result;
}

void MainWindow::addConstrain() {
    qDebug() << "addConstrain()";
    if (userMode != addConstrainMode) {
        qDebug() << "[diag] addConstrain:: userMode is invalid, no addition should be done";
        QMessageBox errBox;
        errBox.setText("Cannot add constrain with inactive AddConstrainMode");
        errBox.exec();
    }
    status->showMessage("add Costrain not implemented yet!", 5000);
}
/*
 * SLOTS impl. END
 */

bool sleepy() {
    QThread::sleep(5); // sleep for 5 seconds;
    return false;
}


void MainWindow::drawCircuit() {
    const double SHIFT = 100;
    double min_x, min_y, max_x, max_y;

    if (objects.length() == 0)
        return;

    min_x = max_x = objects[0]->get_image()[0].x;
    min_y = max_y = objects[0]->get_image()[0].y;

    foreach (GrObject* obj, objects) {
        foreach (GrShape shape, obj->get_image()) {
            min_x = qMin(min_x, shape.x);
            min_y = qMin(min_y, shape.y);
            max_x = qMax(max_x, shape.x);
            max_y = qMax(max_y, shape.y);
        }
    }

    scene->clear();
    scene->setSceneRect(QRectF(0, 0, max_x - min_x + 2 * SHIFT, max_y - min_y + 2 * SHIFT));

    auto getSceneX = [min_x, SHIFT](double x){ return x - min_x + SHIFT; };
    auto getSceneY = [max_y, SHIFT](double y){ return qAbs(y - max_y) + SHIFT; };
    foreach (GrObject* obj, objects) {
        double x, y;
        foreach (GrShape shape, obj->get_image()) {
            switch (shape.type) {
            case GrShape::MoveTo:
                x = shape.x;
                y = shape.y;
                break;
            case GrShape::LineTo:
                if (!shape.options && GrShape::Hidden)
                    scene->addLine(getSceneX(x), getSceneY(y),
                                   getSceneX(shape.x), getSceneY(shape.y));
                x = shape.x;
                y = shape.y;
                break;
            case GrShape::ArcTo:
                //scene->addEllipse();
                break;
            case GrShape::ClosePath:
            default:
                break;
            }
        }
    }
}
